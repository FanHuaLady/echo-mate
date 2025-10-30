#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include "flower_weather_app.h"

// 内部回调函数：接收API响应数据（静态函数，仅内部使用）
static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    size_t total = size * nmemb;
    char **buffer = (char **)stream;

    size_t current_len = *buffer ? strlen(*buffer) : 0;
    char *new_buffer = realloc(*buffer, current_len + total + 1);
    if (new_buffer == NULL) 
    {
        fprintf(stderr, "Memory allocation failed in write_callback\n");
        return 0;
    }

    *buffer = new_buffer;
    memcpy(*buffer + current_len, ptr, total);
    (*buffer)[current_len + total] = '\0';
    return total;
}

// 内部函数：解析JSON数据到结构体（静态函数，仅内部使用）
static int parse_weather_json(const char *json, FlowerWeather *weather) 
{
    if (json == NULL || weather == NULL) 
    {
        fprintf(stderr, "Invalid parameter in parse_weather_json\n");
        return -1;
    }

    // 初始化结构体（清空字符串）
    memset(weather, 0, sizeof(FlowerWeather));

    // JSON解析初始化
    struct json_tokener *tok = json_tokener_new();
    struct json_object *root = json_tokener_parse_ex(tok, json, strlen(json));

    if (tok->err != json_tokener_success) 
    {
        const char *err_msg = "Unknown error";
        // 手动映射json_tokener_error_t错误码（不依赖库函数）
        switch (tok->err) 
        {
            case json_tokener_success: err_msg = "Success"; break;
            case json_tokener_continue: err_msg = "Incomplete JSON data"; break;
            case json_tokener_error_depth: err_msg = "Exceed max nesting depth"; break;
            case json_tokener_error_parse_eof: err_msg = "Unexpected end of input"; break;
            case json_tokener_error_parse_unexpected: err_msg = "Unexpected character"; break;
            case json_tokener_error_parse_null: err_msg = "Invalid null value"; break;
            case json_tokener_error_parse_boolean: err_msg = "Invalid boolean value"; break;
            case json_tokener_error_parse_number: err_msg = "Invalid number"; break;
            case json_tokener_error_parse_string: err_msg = "Invalid string"; break;
            case json_tokener_error_parse_array: err_msg = "Invalid array"; break;
            case json_tokener_error_parse_comment: err_msg = "Invalid comment"; break;
            default: err_msg = "Unknown parse error"; break;
        }
        fprintf(stderr, "JSON parse error: %s (code: %d)\n", err_msg, tok->err);
        json_tokener_free(tok);
        return -1;
    }
    json_tokener_free(tok);

    // 检查API响应码
    struct json_object *code_obj = json_object_object_get(root, "code");
    if (code_obj == NULL || strcmp(json_object_get_string(code_obj), "200") != 0) {
        fprintf(stderr, "API request failed, code: %s\n", 
                code_obj ? json_object_get_string(code_obj) : "unknown");
        json_object_put(root);
        return -1;
    }

    // 获取实时天气数据对象
    struct json_object *now_obj = json_object_object_get(root, "now");
    if (now_obj == NULL) {
        fprintf(stderr, "No real-time weather data found\n");
        json_object_put(root);
        return -1;
    }

    // 提取字段（缺失时填"N/A"）
    #define GET_FIELD_AND_COPY(obj, key, dest, max_len) do { \
        struct json_object *field = json_object_object_get(obj, key); \
        if (field != NULL) { \
            strncpy(dest, json_object_get_string(field), max_len - 1); \
            dest[max_len - 1] = '\0'; \
        } else { \
            strncpy(dest, "N/A", max_len - 1); \
            dest[max_len - 1] = '\0'; \
        } \
    } while(0)

    // 填充结构体字段（对应weather、temperature、humidity、windpower）
    GET_FIELD_AND_COPY(now_obj, "text", weather->weather, sizeof(weather->weather));
    GET_FIELD_AND_COPY(now_obj, "temp", weather->temperature, sizeof(weather->temperature));
    GET_FIELD_AND_COPY(now_obj, "humidity", weather->humidity, sizeof(weather->humidity));
    GET_FIELD_AND_COPY(now_obj, "windScale", weather->windpower, sizeof(weather->windpower));

    // 释放JSON对象
    json_object_put(root);
    return 0;
}

// 对外接口实现：获取天气信息
FlowerWeather* flower_weather_get_info(void) 
{
    CURL *curl = NULL;
    CURLcode res;
    char *response = NULL;
    FlowerWeather *weather = NULL;
    char api_url[512] = {0};

    // 1. 分配结构体内存
    weather = (FlowerWeather*)malloc(sizeof(FlowerWeather));
    if (weather == NULL) 
    {
        fprintf(stderr, "Malloc FlowerWeather failed\n");
        return NULL;
    }

    // 2. 构建完整API地址（拼接CITY_ID）
    snprintf(api_url, sizeof(api_url), API_URL, CITY_ID);

    // 3. 初始化curl
    curl = curl_easy_init();
    if (curl == NULL) 
    {
        fprintf(stderr, "curl initialization failed\n");
        flower_weather_free(weather);
        return NULL;
    }

    // 4. 配置curl参数
    curl_easy_setopt(curl, CURLOPT_URL, api_url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    // 5. 添加请求头（API密钥）
    struct curl_slist *headers = NULL;
    char api_key_header[128] = {0};
    snprintf(api_key_header, sizeof(api_key_header), "X-QW-Api-Key: %s", API_KEY);
    headers = curl_slist_append(headers, api_key_header);
    headers = curl_slist_append(headers, "Accept: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // 6. 发起API请求
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) 
    {
        fprintf(stderr, "API request failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        free(response);
        flower_weather_free(weather);
        return NULL;
    }

    // 7. 解析JSON数据到结构体
    if (response != NULL && strlen(response) > 0) 
    {
        if (parse_weather_json(response, weather) != 0) 
        {
            fprintf(stderr, "Parse weather data failed\n");
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            free(response);
            flower_weather_free(weather);
            return NULL;
        }
    } 
    else 
    {
        fprintf(stderr, "API returned empty response\n");
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        free(response);
        flower_weather_free(weather);
        return NULL;
    }

    // 8. 清理资源
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(response);

    return weather;
}

// 对外接口实现：释放天气信息内存
void flower_weather_free(FlowerWeather* weather) 
{
    if (weather != NULL) 
    {
        free(weather);
        weather = NULL;
    }
}
