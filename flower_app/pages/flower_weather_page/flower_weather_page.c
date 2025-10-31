#include "../../common/flower_page_manager/flower_page_manager.h"
#include "../../common/flower_time_manager/flower_time_manager.h"
#include "flower_weather_app.h"
#include "flower_weather_page.h"
#include <time.h>
#include <stdio.h>

static char * day[] = { "Sun.", "Mon.", "Tues.", "Wed.", "Thurs.", "Fri.", "Sat." };

lv_obj_t * ui_ImgCloud;
lv_obj_t * ui_LabelCity;
lv_obj_t * ui_LabelDate;
lv_obj_t * ui_LabelTemp;
lv_obj_t * ui_LabelWeather;
lv_obj_t * ui_LabelWind;
lv_obj_t * ui_LabelHumi;
lv_timer_t * ui_weather_timer;

static void weather_timer_cb(lv_timer_t *timer)
{
    if(timer == NULL) return;

    // 获取最新天气数据
    FlowerWeather *weather = flower_weather_get_info();
    if (weather == NULL) 
    {
        printf("Failed to get weather info (timer update)\n");
        return;
    }

    char str[36];

    // 更新日期
    /*
    struct tm *t = flower_time_get_local_time();
    if (t != NULL) 
    {
        sprintf(str, "%02d.%02d %s", t->tm_mon + 1, t->tm_mday, day[t->tm_wday]);
        lv_label_set_text(ui_LabelDate, str);
        
        // 如果需要，可以显示时间同步状态
        if (!flower_time_is_synced()) 
        {
            printf("Warning: Using unsynchronized system time\n");
        }
    } 
    else 
    {
        printf("Failed to get local time\n");
    }
    */

    // 更新核心天气数据
    lv_label_set_text(ui_LabelCity,"石家庄");
    sprintf(str, "%s°", weather->temperature ? weather->temperature : "25");
    lv_label_set_text(ui_LabelTemp, str);
    lv_label_set_text(ui_LabelWeather, weather->weather ? weather->weather : "Sunny");
    lv_label_set_text(ui_LabelWind, weather->windpower ? weather->windpower : "3级");
    sprintf(str, "%s%%", weather->humidity ? weather->humidity : "50");
    lv_label_set_text(ui_LabelHumi, str);

    flower_weather_free(weather);                                                       // 释放天气数据资源
    lv_refr_now(NULL);
}

static void exit_btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)  // 仅响应点击事件
    {
        printf("Exit button clicked, return to HomePage\n");
        flower_pm_switch_page("HomePage");
    }
}

void flower_weather_page_init(void) 
{
    lv_obj_t * weather_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(weather_screen, LV_OBJ_FLAG_SCROLLABLE);

    /*
    flower_lib_pm_page_t *self = find_page("WeatherPage");
    if (self != NULL) 
    {
        self->page_obj = weather_screen;
        printf("WeatherPage page_obj assigned: %p\n", self->page_obj);

    }
    */

    FlowerWeather *weather = flower_weather_get_info();
    if (weather == NULL) 
    {
        printf("Failed to get weather info\n");
    }

    lv_obj_set_style_bg_color(weather_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(weather_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 太阳图片
    lv_obj_t * ui_ImgSun = lv_image_create(weather_screen);
    lv_image_set_src(ui_ImgSun, &ui_img_sun_png);
    lv_obj_set_width(ui_ImgSun, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImgSun, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImgSun, 95);
    lv_obj_set_y(ui_ImgSun, -45);
    lv_obj_set_align(ui_ImgSun, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgSun, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_flag(ui_ImgSun, LV_OBJ_FLAG_SCROLLABLE);
    lv_image_set_scale(ui_ImgSun, 208);

    // 云朵图片
    ui_ImgCloud = lv_image_create(weather_screen);
    lv_image_set_src(ui_ImgCloud, &ui_img_clouds_png);
    lv_obj_set_width(ui_ImgCloud, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImgCloud, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImgCloud, 105);
    lv_obj_set_y(ui_ImgCloud, -60);
    lv_obj_set_align(ui_ImgCloud, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgCloud, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_flag(ui_ImgCloud, LV_OBJ_FLAG_SCROLLABLE);
    lv_image_set_scale(ui_ImgCloud, 206);

    // 信息面板
    lv_obj_t * ui_LabelsPanel = lv_obj_create(weather_screen);
    lv_obj_set_width(ui_LabelsPanel, 200);
    lv_obj_set_height(ui_LabelsPanel, 240);
    lv_obj_set_x(ui_LabelsPanel, -50);
    lv_obj_set_y(ui_LabelsPanel, 0);
    lv_obj_set_align(ui_LabelsPanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_LabelsPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_LabelsPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LabelsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_LabelsPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_LabelsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 城市标签
    ui_LabelCity = lv_label_create(ui_LabelsPanel);
    lv_obj_set_width(ui_LabelCity, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelCity, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelCity, -10);
    lv_obj_set_y(ui_LabelCity, 0);
    lv_obj_set_align(ui_LabelCity, LV_ALIGN_TOP_MID);
    char str[36];
    sprintf(str, "%s", "石家庄");
    lv_label_set_text(ui_LabelCity, str);
    lv_obj_set_style_text_font(ui_LabelCity, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 日期标签
    ui_LabelDate = lv_label_create(ui_LabelsPanel);
    lv_obj_set_width(ui_LabelDate, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelDate, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelDate, -10);
    lv_obj_set_y(ui_LabelDate, 30);
    lv_obj_set_align(ui_LabelDate, LV_ALIGN_TOP_MID);
    sprintf(str, "%02d.%02d %s", 10,30, day[3]);
    lv_label_set_text(ui_LabelDate, str);
    lv_obj_set_style_text_color(ui_LabelDate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelDate, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelDate, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 温度标签
    ui_LabelTemp = lv_label_create(ui_LabelsPanel);
    lv_obj_set_width(ui_LabelTemp, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelTemp, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelTemp, 0);
    lv_obj_set_y(ui_LabelTemp, 5);
    lv_obj_set_align(ui_LabelTemp, LV_ALIGN_CENTER);
    sprintf(str, "%s°", weather->temperature);
    lv_label_set_text(ui_LabelTemp, str);
    lv_obj_set_style_text_font(ui_LabelTemp, &ui_font_NuberBig90, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 天气状况标签
    ui_LabelWeather = lv_label_create(ui_LabelsPanel);
    lv_obj_set_width(ui_LabelWeather, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelWeather, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelWeather, -10);
    lv_obj_set_y(ui_LabelWeather, 150);
    lv_obj_set_align(ui_LabelWeather, LV_ALIGN_TOP_MID);
    sprintf(str, "%s", weather->weather);
    lv_label_set_text(ui_LabelWeather, str);
    lv_obj_set_style_text_color(ui_LabelWeather, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWeather, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWeather, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 底部信息面板
    lv_obj_t * ui_BtmLabelsPanel = lv_obj_create(weather_screen);
    lv_obj_set_width(ui_BtmLabelsPanel, 320);
    lv_obj_set_height(ui_BtmLabelsPanel, 50);
    lv_obj_set_x(ui_BtmLabelsPanel, 0);
    lv_obj_set_y(ui_BtmLabelsPanel, 95);
    lv_obj_set_align(ui_BtmLabelsPanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_BtmLabelsPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_BtmLabelsPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtmLabelsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BtmLabelsPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BtmLabelsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 风力图标和标签
    lv_obj_t * ui_IconWind = lv_label_create(ui_BtmLabelsPanel);
    lv_obj_set_width(ui_IconWind, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_IconWind, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_IconWind, -70);
    lv_obj_set_y(ui_IconWind, 0);
    lv_obj_set_align(ui_IconWind, LV_ALIGN_CENTER);
    lv_label_set_text(ui_IconWind, "");
    lv_obj_set_style_text_color(ui_IconWind, lv_color_hex(0xEEB27D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_IconWind, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_IconWind, &ui_font_iconfont30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelWind = lv_label_create(ui_BtmLabelsPanel);
    lv_obj_set_width(ui_LabelWind, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelWind, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelWind, -35);
    lv_obj_set_y(ui_LabelWind, 0);
    lv_obj_set_align(ui_LabelWind, LV_ALIGN_CENTER);
    sprintf(str, "%s", weather->windpower);
    lv_label_set_text(ui_LabelWind, str);
    lv_obj_set_style_text_color(ui_LabelWind, lv_color_hex(0xEEB27D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWind, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWind, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 湿度图标和标签
    lv_obj_t * ui_IconHumi = lv_label_create(ui_BtmLabelsPanel);
    lv_obj_set_width(ui_IconHumi, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_IconHumi, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_IconHumi, 35);
    lv_obj_set_y(ui_IconHumi, 0);
    lv_obj_set_align(ui_IconHumi, LV_ALIGN_CENTER);
    lv_label_set_text(ui_IconHumi, "");
    lv_obj_set_style_text_color(ui_IconHumi, lv_color_hex(0x42D2F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_IconHumi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_IconHumi, &ui_font_iconfont30, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 湿度标签
    ui_LabelHumi = lv_label_create(ui_BtmLabelsPanel);
    lv_obj_set_width(ui_LabelHumi, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelHumi, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelHumi, 75);
    lv_obj_set_y(ui_LabelHumi, 1);
    lv_obj_set_align(ui_LabelHumi, LV_ALIGN_CENTER);
    sprintf(str, "%s%%", weather->humidity);
    lv_label_set_text(ui_LabelHumi, str);
    lv_obj_set_style_text_color(ui_LabelHumi, lv_color_hex(0x42D2F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelHumi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHumi, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);

    flower_weather_free(weather);

    // ui_weather_timer = lv_timer_create(weather_timer_cb, 5000, NULL);

    // lv_obj_add_event_cb(page, gesture_back_event_cb, LV_EVENT_ALL, NULL);

    // 新增：退出按钮（右上角）
    lv_obj_t *ui_ExitBtn = lv_btn_create(weather_screen);
    lv_obj_set_width(ui_ExitBtn, 60);    // 按钮宽度
    lv_obj_set_height(ui_ExitBtn, 30);   // 按钮高度
    lv_obj_set_x(ui_ExitBtn, 130);       // 右偏移（适配320px宽屏幕）
    lv_obj_set_y(ui_ExitBtn, -100);      // 上偏移
    lv_obj_set_align(ui_ExitBtn, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_ExitBtn, LV_OBJ_FLAG_SCROLLABLE);
    // 按钮默认样式（黑色背景+白色边框）
    lv_obj_set_style_bg_color(ui_ExitBtn, lv_color_hex(0x1A1A1A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ExitBtn, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ExitBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ExitBtn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ExitBtn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_ExitBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);  // 圆角
    // 按钮按下样式（灰色背景）
    lv_obj_set_style_bg_color(ui_ExitBtn, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_ExitBtn, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    // 退出按钮文字
    lv_obj_t *ui_ExitBtnLabel = lv_label_create(ui_ExitBtn);
    lv_label_set_text(ui_ExitBtnLabel, "Exit");
    lv_obj_set_style_text_color(ui_ExitBtnLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ExitBtnLabel, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_ExitBtnLabel);  // 文字居中

    // 绑定退出按钮回调
    lv_obj_add_event_cb(ui_ExitBtn, exit_btn_event_cb, LV_EVENT_ALL, NULL);

    lv_scr_load_anim(weather_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);
}

void flower_weather_page_deinit(void) 
{
    // lv_timer_delete(ui_weather_timer);
}
