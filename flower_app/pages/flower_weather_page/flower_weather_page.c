#include "../../common/flower_page_manager/flower_page_manager.h"
#include "flower_weather_app.h"
#include "flower_weather_page.h"
#include <stdio.h>

// 按钮1回调：返回主界面
static void btn_back_event_cb(lv_event_t *e) 
{
    lv_event_stop_bubbling(e);
    flower_pm_switch_page("HomePage");
}

void flower_weather_page_init(lv_obj_t *page) 
{
    FlowerWeather *weather = flower_weather_get_info();
    if (weather == NULL) 
    {
        printf("Failed to get weather info\n");
    }

    printf("===== Current Weather Info =====\n");
    printf("Weather: %s\n", weather->weather);
    printf("Temperature: %s °C\n", weather->temperature);
    printf("Humidity: %s %%\n", weather->humidity);
    printf("Wind Power: %s 级\n", weather->windpower);
    printf("===============================\n");

    flower_weather_free(weather);

    lv_obj_t *btn_back = lv_btn_create(page);
    lv_obj_set_size(btn_back, 150, 50);                                         // 设置按钮大小
    lv_obj_set_style_bg_color(btn_back, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(btn_back, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(btn_back, btn_back_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *btn_back_label = lv_label_create(btn_back);
    lv_label_set_text(btn_back_label, "RETURN HOME");
    lv_obj_center(btn_back_label);
    lv_refr_now(NULL);
}

void flower_weather_page_deinit(lv_obj_t *page) 
{
    (void)page;
}
