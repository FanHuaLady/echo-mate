#include "flower_ui.h"

// （可选）参考gui_app的页面管理，若简单场景可省略
// static lv_lib_pm_t flower_page_manager;

// 按钮点击回调（核心功能）
static void btn_click_handler(lv_event_t *e) 
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_label_set_text(lv_obj_get_child(btn, 0), "Clicked!");
    flower_msgbox_info("Success", "Button clicked!");                   // 调用消息框
}

static void msgbox_close_click_event_cb(lv_event_t *e) {
    lv_obj_t *mbox = lv_event_get_target(e);
    bool *mbox_exist = lv_event_get_user_data(e);
    lv_msgbox_close(mbox);
    *mbox_exist = false;
}

void flower_msgbox_info(const char *title, const char *text) 
{
    static lv_obj_t *current_mbox;
    static bool mbox_exist = false;

    if (mbox_exist) {
        lv_msgbox_close(current_mbox);
        mbox_exist = false;
    }

    current_mbox = lv_msgbox_create(NULL);
    mbox_exist = true;
    lv_msgbox_add_title(current_mbox, title);
    lv_msgbox_add_text(current_mbox, text);
    lv_obj_t *close_btn = lv_msgbox_add_close_button(current_mbox);
    // 用 C 风格的函数指针 + 用户数据绑定事件
    lv_obj_add_event_cb(close_btn, msgbox_close_click_event_cb, LV_EVENT_PRESSED, &mbox_exist);
}

// 核心初始化函数（对齐ui_init的结构）
void flower_ui_init(void) 
{
    lv_disp_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, 
                                             lv_palette_main(LV_PALETTE_GREEN), 
                                             lv_palette_main(LV_PALETTE_ORANGE),
                                             true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 120, 50);
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, btn_click_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Click Me");
    lv_obj_center(label);
}
