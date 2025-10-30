#include "../../common/flower_page_manager/flower_page_manager.h"
#include "flower_weather_app.h"
#include "flower_weather_page.h"
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

// 按钮1回调：返回主界面
static void gesture_back_event_cb(lv_event_t *e) 
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_GESTURE)
    {
        if(lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT || lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
        {
            flower_pm_switch_page("HomePage");
        }
    }
}

void flower_weather_page_init(lv_obj_t *page) 
{
    FlowerWeather *weather = flower_weather_get_info();
    if (weather == NULL) 
    {
        printf("Failed to get weather info\n");
    }

    lv_obj_set_style_bg_color(page, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(page, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 太阳图片
    lv_obj_t * ui_ImgSun = lv_image_create(page);
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
    ui_ImgCloud = lv_image_create(page);
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
    lv_obj_t * ui_LabelsPanel = lv_obj_create(page);
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
    sprintf(str, "%s", "Shijiazhuang");
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
    lv_obj_t * ui_BtmLabelsPanel = lv_obj_create(page);
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

    /*
    lv_obj_t *btn_back = lv_btn_create(page);
    lv_obj_set_size(btn_back, 60, 40);                                         // 设置按钮大小
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_LEFT, 0, 20);
    lv_obj_set_style_bg_color(btn_back, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(btn_back, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(btn_back, btn_back_event_cb, LV_EVENT_CLICKED, NULL);
    */

    lv_obj_add_event_cb(page, gesture_back_event_cb, LV_EVENT_ALL, NULL);

//  lv_obj_add_event_cb(page, back_event_Gesture, LV_EVENT_ALL, NULL);
    lv_refr_now(NULL);
}

void flower_weather_page_deinit(lv_obj_t *page) 
{
    
}
