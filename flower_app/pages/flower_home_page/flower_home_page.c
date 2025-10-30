#include "../../common/flower_page_manager/flower_page_manager.h"
#include "flower_home_page.h"
#include <stdio.h>

// LED页面按钮回调：跳转到LED页面
static void led_btn_click_event_cb(lv_event_t *e) 
{
    lv_event_stop_bubbling(e);
    flower_pm_switch_page("LEDPage");
}

// 天气页面按钮回调：跳转到天气页面
static void weather_btn_click_event_cb(lv_event_t *e) 
{
    lv_event_stop_bubbling(e);
    flower_pm_switch_page("WeatherPage");
}

// 首页初始化
void flower_home_page_init(lv_obj_t *page) 
{
    // 关于LED应用图标
    lv_obj_t *ui_MemoBtn = lv_button_create(page);                          // 创建按钮
    lv_obj_set_width(ui_MemoBtn, 70);                                       // 设置宽度
    lv_obj_set_height(ui_MemoBtn, 70);                                      // 设置高度
    lv_obj_set_x(ui_MemoBtn, 15);
    lv_obj_set_y(ui_MemoBtn, 55);
    lv_obj_set_align(ui_MemoBtn, LV_ALIGN_LEFT_MID);                        // 左中对齐
    lv_obj_add_flag(ui_MemoBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);               // 可滚动对焦
    lv_obj_remove_flag(ui_MemoBtn, LV_OBJ_FLAG_SCROLLABLE);                 // 不可滚动
    lv_obj_set_style_radius(ui_MemoBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MemoBtn, lv_color_hex(0xB83B5E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MemoBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui_MemoBtn, &ui_img_memo64_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_MemoBtn, led_btn_click_event_cb, LV_EVENT_CLICKED, "LEDPage");

    // 关于天气应用图标
    lv_obj_t * ui_WeatherBtn = lv_button_create(page);
    lv_obj_set_width(ui_WeatherBtn, 70);
    lv_obj_set_height(ui_WeatherBtn, 70);
    lv_obj_set_x(ui_WeatherBtn, 110);
    lv_obj_set_y(ui_WeatherBtn, -45);
    lv_obj_set_align(ui_WeatherBtn, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_WeatherBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_remove_flag(ui_WeatherBtn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_WeatherBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui_WeatherBtn, &ui_img_weather64_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_WeatherBtn, weather_btn_click_event_cb, LV_EVENT_CLICKED, "WeatherPage");
}

// 首页销毁：空实现（如需释放资源可在此添加）
void flower_home_page_deinit(lv_obj_t *page) 
{
    (void)page;
}
