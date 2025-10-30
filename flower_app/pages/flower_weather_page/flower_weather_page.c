#include "../../common/flower_page_manager/flower_page_manager.h"
#include <stdio.h>

// 按钮1回调：返回主界面
static void btn_back_event_cb(lv_event_t *e) 
{
    lv_event_stop_bubbling(e);
    printf("Returning to Home Page\n");
    flower_pm_switch_page("HomePage");
}

void flower_weather_page_init(lv_obj_t *page) 
{
    lv_obj_t *btn_back = lv_btn_create(page);
    lv_obj_set_size(btn_back, 150, 50);
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
