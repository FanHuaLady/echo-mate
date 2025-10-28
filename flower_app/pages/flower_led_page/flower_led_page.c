#include "../../common/flower_page_manager/flower_page_manager.h"
#include "flower_led_page.h"
#include <stdio.h>

// 按钮1回调：返回主界面
static void btn_back_event_cb(lv_event_t *e) 
{
    lv_event_stop_bubbling(e);
    printf("Returning to Home Page\n");
    flower_pm_switch_page("HomePage");
}

// LED页面初始化：创建两个按钮
void flower_led_page_init(lv_obj_t *page) {
    printf("=== LED Page Init Start ===\n");
    printf("Page pointer: %p\n", page);
    
    // 设置页面背景色以便调试
    lv_obj_set_style_bg_color(page, lv_color_hex(0x404040), 0);
    lv_obj_set_style_bg_opa(page, LV_OPA_COVER, 0);
    
    // 标题
    lv_obj_t *title = lv_label_create(page);
    lv_label_set_text(title, "LED Page - Active");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    printf("Title created: %p\n", title);

    // 按钮1：返回主界面
    lv_obj_t *btn_back = lv_btn_create(page);
    printf("Button created: %p\n", btn_back);
    
    lv_obj_set_size(btn_back, 150, 50);
    // lv_obj_align(btn_back, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align_to(btn_back, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 80);
    // 设置按钮样式以便调试
    lv_obj_set_style_bg_color(btn_back, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(btn_back, LV_OPA_COVER, 0);
    
    // 绑定事件
    lv_obj_add_event_cb(btn_back, btn_back_event_cb, LV_EVENT_CLICKED, NULL);
    printf("Event callback registered\n");
    
    // 按钮标签
    lv_obj_t *btn_back_label = lv_label_create(btn_back);
    lv_label_set_text(btn_back_label, "RETURN HOME");
    lv_obj_center(btn_back_label);
    printf("Button label created: %p\n", btn_back_label);
    
    // 测试直接调用事件回调
    printf("Testing direct callback call...\n");
    // btn_back_event_cb(NULL); // 取消注释测试回调函数本身
    
    printf("=== LED Page Init End ===\n");
    
    // 强制刷新显示
    lv_refr_now(NULL);
}

// LED页面销毁：空实现（如需释放资源可在此添加）
void flower_led_page_deinit(lv_obj_t *page) {
    (void)page;
}
