#ifndef _FLOWER_WEATHER_APP_H
#define _FLOWER_WEATHER_APP_H

#define API_KEY "5fe131843abc451dbac21847483eb7d2"   
#define CITY_ID "101010100"            
#define API_URL "https://m76fr7aq3e.re.qweatherapi.com/v7/weather/now?location=%s"

typedef struct {
    char weather[32];                                           // 天气状况
    char temperature[16];                                       // 温度
    char humidity[16];                                          // 湿度
    char windpower[16];                                         // 风力
} FlowerWeather;

FlowerWeather* flower_weather_get_info(void);                   // 获取天气信息
void flower_weather_free(FlowerWeather* weather);               // 释放天气信息内存

#endif
