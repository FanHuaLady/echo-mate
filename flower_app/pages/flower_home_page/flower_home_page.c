#include "../../common/flower_page_manager/flower_page_manager.h"
#include "flower_home_page.h"
#include <stdio.h>

// 定义事件回调函数（C 风格）
static void btn_click_event_cb(lv_event_t *e) 
{
    lv_event_stop_bubbling(e);
    printf("Switching to LED Page\n");
    flower_pm_switch_page("LEDPage");
}

// 
void flower_home_page_init(lv_obj_t *page) 
{
    lv_obj_t *ui_MemoBtn = lv_button_create(page);
    lv_obj_set_width(ui_MemoBtn, 70);
    lv_obj_set_height(ui_MemoBtn, 70);
    lv_obj_set_x(ui_MemoBtn, 15);
    lv_obj_set_y(ui_MemoBtn, 55);
    lv_obj_set_align(ui_MemoBtn, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_MemoBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_MemoBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_MemoBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MemoBtn, lv_color_hex(0xB83B5E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MemoBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui_MemoBtn, &ui_img_memo64_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    // event
    lv_obj_add_event_cb(ui_MemoBtn, btn_click_event_cb, LV_EVENT_CLICKED, "MemoPage");
}


// 首页销毁：空实现（如需释放资源可在此添加）
void flower_home_page_deinit(lv_obj_t *page) 
{
    (void)page;
}