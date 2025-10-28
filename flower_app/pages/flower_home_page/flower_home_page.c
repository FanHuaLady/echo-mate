#include "flower_home_page.h"

// 定义事件回调函数（C 风格）
static void btn_click_event_cb(lv_event_t *e) 
{
    flower_pm_switch_page("DetailPage");
}

// 首页初始化：创建“切换到详情页”按钮
void flower_home_page_init(lv_obj_t *page) 
{
    // 标题
    lv_obj_t *title = lv_label_create(page);
    lv_label_set_text(title, "首页");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    // 切换按钮
    lv_obj_t *btn = lv_btn_create(page);
    lv_obj_set_size(btn, 150, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    
    // 绑定事件：使用函数指针，无用户数据传 NULL
    lv_obj_add_event_cb(btn, btn_click_event_cb, LV_EVENT_CLICKED, NULL);

    // 按钮文本
    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "去详情页");
    lv_obj_center(btn_label);
}


// 首页销毁：空实现（如需释放资源可在此添加）
void flower_home_page_deinit(lv_obj_t *page) {
    (void)page;
}