#include "../../common/flower_page_manager/flower_page_manager.h"
#include "flower_echo_page.h"
#include <stdio.h>

lv_obj_t * ui_EyesPanel;                                                // 眼睛面板
lv_obj_t * ui_EyesVerMovePanel;                                         // 眼睛垂直移动面板
lv_obj_t * ui_QuestionImg;                                              // 问题图像
lv_obj_t * ui_thinkImg;                                                 // 思考图像
lv_obj_t * ui_HandImg;                                                  // 手部图像
lv_obj_t * ui_EyeRight;                                                 // 右眼
lv_obj_t * ui_EyeLeft;                                                  // 左眼
lv_obj_t * ui_MouthPanel;                                               // 嘴部面板
lv_obj_t * ui_Mouth;                                                    // 嘴部
lv_obj_t * ui_LabelInfo;                                                // 信息标签
// lv_timer_t * ui_ChatBot_timer;                                          // 聊天机器人定时器
// lv_timer_t * ui_ChatBot_move_timer;                                     // 聊天机器人移动定时器

static void exit_btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        printf("Exit button clicked, return to HomePage\n");
        flower_pm_switch_page("HomePage");
    }
}

void flower_echo_page_init(void)
{
    lv_obj_t * echo_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(echo_screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(echo_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(echo_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EyesPanel = lv_obj_create(echo_screen);                          // 创建眼睛面板
    lv_obj_set_width(ui_EyesPanel, 210);
    lv_obj_set_height(ui_EyesPanel, 80);
    lv_obj_set_x(ui_EyesPanel, 0);
    lv_obj_set_y(ui_EyesPanel, -25);
    lv_obj_set_align(ui_EyesPanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_EyesPanel, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(ui_EyesPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_EyesPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_EyesPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_EyesPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EyesVerMovePanel = lv_obj_create(ui_EyesPanel);                  // 创建眼睛垂直移动面板
    lv_obj_set_width(ui_EyesVerMovePanel, 210);
    lv_obj_set_height(ui_EyesVerMovePanel, 80);
    lv_obj_set_align(ui_EyesVerMovePanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_EyesVerMovePanel, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(ui_EyesVerMovePanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_EyesVerMovePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_EyesVerMovePanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_EyesVerMovePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EyeRight = lv_button_create(ui_EyesVerMovePanel);                // 创建右眼
    lv_obj_set_width(ui_EyeRight, 80);
    lv_obj_set_height(ui_EyeRight, 80);
    lv_obj_set_x(ui_EyeRight, 60);
    lv_obj_set_y(ui_EyeRight, 0);
    lv_obj_set_align(ui_EyeRight, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_EyeRight, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_remove_flag(ui_EyeRight, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_EyeRight, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_EyeRight, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_EyeRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EyeLeft = lv_button_create(ui_EyesVerMovePanel);                 // 创建左眼
    lv_obj_set_width(ui_EyeLeft, 80);
    lv_obj_set_height(ui_EyeLeft, 80);
    lv_obj_set_x(ui_EyeLeft, -60);
    lv_obj_set_y(ui_EyeLeft, 0);
    lv_obj_set_align(ui_EyeLeft, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_EyeLeft, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_remove_flag(ui_EyeLeft, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_EyeLeft, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_EyeLeft, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_EyeLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MouthPanel = lv_obj_create(echo_screen);                         // 创建嘴部面板
    lv_obj_set_width(ui_MouthPanel, 80);
    lv_obj_set_height(ui_MouthPanel, 80);
    lv_obj_set_x(ui_MouthPanel, 0);
    lv_obj_set_y(ui_MouthPanel, 95);
    lv_obj_set_align(ui_MouthPanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_MouthPanel, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(ui_MouthPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MouthPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MouthPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MouthPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mouth = lv_button_create(ui_MouthPanel);                         // 创建嘴部
    lv_obj_set_width(ui_Mouth, 60);                                     
    lv_obj_set_height(ui_Mouth, 60);
    lv_obj_set_x(ui_Mouth, 0);
    lv_obj_set_y(ui_Mouth, -40);
    lv_obj_set_align(ui_Mouth, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Mouth, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_remove_flag(ui_Mouth, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_Mouth, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Mouth, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Mouth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_QuestionImg = lv_image_create(echo_screen);                      // 创建问题图像
    lv_image_set_src(ui_QuestionImg, &ui_img_question60_png);
    lv_obj_set_width(ui_QuestionImg, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_QuestionImg, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_QuestionImg, 125);
    lv_obj_set_y(ui_QuestionImg, -80);
    lv_obj_set_align(ui_QuestionImg, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_QuestionImg, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_opa(ui_QuestionImg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_thinkImg = lv_image_create(echo_screen);
    lv_image_set_src(ui_thinkImg, &ui_img_think60_png);
    lv_obj_set_width(ui_thinkImg, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_thinkImg, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_thinkImg, 120);
    lv_obj_set_y(ui_thinkImg, -80);
    lv_obj_set_align(ui_thinkImg, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_thinkImg, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_opa(ui_thinkImg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HandImg = lv_image_create(echo_screen);
    lv_image_set_src(ui_HandImg, &ui_img_hand60_png);
    lv_obj_set_width(ui_HandImg, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_HandImg, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_HandImg, 0);
    lv_obj_set_y(ui_HandImg, 55);
    lv_obj_set_align(ui_HandImg, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_HandImg, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_rotation(ui_HandImg, -350);
    lv_obj_set_style_opa(ui_HandImg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelInfo = lv_label_create(echo_screen);
    lv_obj_set_width(ui_LabelInfo, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInfo, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelInfo, 0);
    lv_obj_set_y(ui_LabelInfo, 10);
    lv_obj_set_align(ui_LabelInfo, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_LabelInfo, "Wait connect ...");
    lv_obj_set_style_text_color(ui_LabelInfo, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInfo, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_LabelInfo, LV_OBJ_FLAG_HIDDEN);

    // 退出按钮
    lv_obj_t *ui_ExitBtn = lv_btn_create(echo_screen);
    lv_obj_set_width(ui_ExitBtn, 60);
    lv_obj_set_height(ui_ExitBtn, 30);
    lv_obj_set_x(ui_ExitBtn, 130);
    lv_obj_set_y(ui_ExitBtn, -100);
    lv_obj_set_align(ui_ExitBtn, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_ExitBtn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ExitBtn, lv_color_hex(0x1A1A1A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ExitBtn, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ExitBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ExitBtn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ExitBtn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_ExitBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);  // 圆角
    lv_obj_set_style_bg_color(ui_ExitBtn, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_ExitBtn, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_t *ui_ExitBtnLabel = lv_label_create(ui_ExitBtn);
    lv_label_set_text(ui_ExitBtnLabel, "Exit");
    lv_obj_set_style_text_color(ui_ExitBtnLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ExitBtnLabel, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_ExitBtnLabel);

    lv_obj_add_event_cb(ui_ExitBtn, exit_btn_event_cb, LV_EVENT_ALL, NULL);
    lv_scr_load_anim(echo_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);
}

void flower_echo_page_deinit(void) 
{
    
}
