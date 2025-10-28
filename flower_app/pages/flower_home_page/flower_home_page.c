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

// 首页初始化：创建“切换到详情页”按钮
void flower_home_page_init(lv_obj_t *page) 
{
    printf("=== Home Page Init Start ===\n");
    
    // 获取屏幕分辨率
    lv_coord_t screen_width = lv_disp_get_hor_res(NULL);
    lv_coord_t screen_height = lv_disp_get_ver_res(NULL);
    printf("Screen resolution: %dx%d\n", screen_width, screen_height);
    printf("Page size: %dx%d\n", lv_obj_get_width(page), lv_obj_get_height(page));
    
    // 标题
    lv_obj_t *title = lv_label_create(page);
    lv_label_set_text(title, "Home");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    // 切换按钮 - 使用基于屏幕分辨率的绝对位置
    lv_obj_t *btn = lv_btn_create(page);
    lv_obj_set_size(btn, 150, 50);
    
    // 设置明显的按钮样式
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x0066FF), 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
    
    // 绑定事件
    lv_obj_add_event_cb(btn, btn_click_event_cb, LV_EVENT_CLICKED, NULL);

    // 按钮文本
    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "led");
    lv_obj_center(btn_label);
    
    printf("=== Home Page Init End ===\n");
}


// 首页销毁：空实现（如需释放资源可在此添加）
void flower_home_page_deinit(lv_obj_t *page) 
{
    (void)page;
}