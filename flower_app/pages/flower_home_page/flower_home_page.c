#include "../../common/flower_page_manager/flower_page_manager.h"
#include "../../common/flower_time_manager/flower_time_manager.h"
#include "flower_home_page.h"
#include <stdio.h>

lv_timer_t * ui_home_timer;                                                 // 获取时间
// lv_obj_t * ui_WifiLabel;
// lv_obj_t * ui_NoWifiLabel;

lv_obj_t * timelabel;                                                       // 时间标签

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

// 时间
static void ui_home_timer_cb(lv_event_t *e)
{
    struct tm *t = flower_time_get_local_time();                                // 获取本地时间
    if(t != NULL)
    {
        char time_str[6];
        sprintf(time_str, "%02d:%02d", t->tm_hour, t->tm_min);
        lv_label_set_text(timelabel, time_str);
    }
}

// 首页初始化
void flower_home_page_init(void) 
{

    printf("初始化首页页面\n");

    lv_obj_t * home_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(home_screen, LV_OBJ_FLAG_SCROLLABLE);

    /*
    flower_lib_pm_page_t *self = find_page("HomePage");
    if (self != NULL) 
    {
        self->page_obj = home_screen;
        printf("HomePage page_obj assigned: %p\n", self->page_obj);
    }
    */
        

    // 时间标签
    timelabel = lv_label_create(home_screen);
    lv_obj_set_width(timelabel, LV_SIZE_CONTENT);
    lv_obj_set_height(timelabel, LV_SIZE_CONTENT);
    lv_obj_set_x(timelabel, 0);
    lv_obj_set_y(timelabel, 5);
    lv_obj_set_align(timelabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(timelabel, "11:59");
    lv_obj_set_style_text_font(timelabel, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    char time_str[6];
    sprintf(time_str, "%02d:%02d", 6, 30);
    lv_label_set_text(timelabel, time_str);

    // 关于LED应用图标
    lv_obj_t *ui_MemoBtn = lv_button_create(home_screen);                   // 创建按钮
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
    lv_obj_t * ui_WeatherBtn = lv_button_create(home_screen);
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

    // 获取时间
    // ui_home_timer = lv_timer_create(ui_home_timer_cb, 5000, NULL);

    lv_scr_load_anim(home_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);
}

void flower_home_page_deinit(void) 
{
    // lv_timer_delete(ui_home_timer);
}
