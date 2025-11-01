#include "../../common/flower_page_manager/flower_page_manager.h"
#include "flower_echo_page.h"
#include <stdio.h>
#include <stdlib.h>

lv_obj_t * ui_EyesPanel;
lv_obj_t * ui_EyesVerMovePanel;
lv_obj_t * ui_QuestionImg;
lv_obj_t * ui_thinkImg;
lv_obj_t * ui_HandImg;
lv_obj_t * ui_EyeRight;
lv_obj_t * ui_EyeLeft;
lv_obj_t * ui_MouthPanel;
lv_obj_t * ui_Mouth;
lv_obj_t * ui_LabelInfo;

// 眨眼动画相关变量
static bool is_animating = false;
static lv_timer_t *blink_timer = NULL;
static lv_anim_t blink_anim_left;  // 为左右眼分别创建动画变量
static lv_anim_t blink_anim_right;

// 前向声明函数
static void blink_timer_cb(lv_timer_t * timer);
static void start_blink_animation(void);

// 眨眼动画执行函数
static void blink_anim_exec_cb(void * obj, int32_t value)
{
    lv_obj_set_height(obj, value);
    lv_obj_set_style_radius(obj, value/2, LV_PART_MAIN | LV_STATE_DEFAULT);
}

// 定时器回调，触发眨眼
static void blink_timer_cb(lv_timer_t * timer)
{
    if (!is_animating) {
        start_blink_animation();
    }
    // 定时器会自动被删除，因为设置了重复次数为1
}

// 开始眨眼动画
static void start_blink_animation(void)
{
    if (is_animating) return;  // 防止重复启动
    
    is_animating = true;
    
    // 为左眼创建动画
    lv_anim_init(&blink_anim_left);
    lv_anim_set_var(&blink_anim_left, ui_EyeLeft);
    lv_anim_set_exec_cb(&blink_anim_left, (lv_anim_exec_xcb_t)blink_anim_exec_cb);
    lv_anim_set_values(&blink_anim_left, 80, 5);
    lv_anim_set_time(&blink_anim_left, 150);
    lv_anim_set_playback_time(&blink_anim_left, 150);
    lv_anim_set_playback_delay(&blink_anim_left, 50);
    lv_anim_set_repeat_count(&blink_anim_left, 1);
    lv_anim_start(&blink_anim_left);
    
    // 为右眼创建相同的动画
    lv_anim_init(&blink_anim_right);
    lv_anim_set_var(&blink_anim_right, ui_EyeRight);
    lv_anim_set_exec_cb(&blink_anim_right, (lv_anim_exec_xcb_t)blink_anim_exec_cb);
    lv_anim_set_values(&blink_anim_right, 80, 5);
    lv_anim_set_time(&blink_anim_right, 150);
    lv_anim_set_playback_time(&blink_anim_right, 150);
    lv_anim_set_playback_delay(&blink_anim_right, 50);
    lv_anim_set_repeat_count(&blink_anim_right, 1);
    lv_anim_start(&blink_anim_right);
    
    // 安排下一次眨眼（使用定时器而不是动画完成回调）
    uint32_t next_blink = 2000 + (rand() % 3000);
    blink_timer = lv_timer_create(blink_timer_cb, next_blink, NULL);
    lv_timer_set_repeat_count(blink_timer, 1);
    is_animating = false;  // 动画开始后就标记为非动画状态，因为LVGL会处理动画执行
}

static void exit_btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        printf("Exit button clicked, return to HomePage\n");
        
        // 退出时清理定时器
        if (blink_timer) {
            lv_timer_del(blink_timer);
            blink_timer = NULL;
        }
        
        flower_pm_switch_page("HomePage");
    }
}

void flower_echo_page_init(void)
{
    lv_obj_t * echo_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(echo_screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(echo_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(echo_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EyesPanel = lv_obj_create(echo_screen);
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

    ui_EyesVerMovePanel = lv_obj_create(ui_EyesPanel);
    lv_obj_set_width(ui_EyesVerMovePanel, 210);
    lv_obj_set_height(ui_EyesVerMovePanel, 80);
    lv_obj_set_align(ui_EyesVerMovePanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_EyesVerMovePanel, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(ui_EyesVerMovePanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_EyesVerMovePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_EyesVerMovePanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_EyesVerMovePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EyeRight = lv_button_create(ui_EyesVerMovePanel);
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

    ui_EyeLeft = lv_button_create(ui_EyesVerMovePanel);
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

    ui_MouthPanel = lv_obj_create(echo_screen);
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

    ui_Mouth = lv_button_create(ui_MouthPanel);
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

    ui_QuestionImg = lv_image_create(echo_screen);
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
    lv_obj_set_style_radius(ui_ExitBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ExitBtn, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_ExitBtn, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_t *ui_ExitBtnLabel = lv_label_create(ui_ExitBtn);
    lv_label_set_text(ui_ExitBtnLabel, "Exit");
    lv_obj_set_style_text_color(ui_ExitBtnLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ExitBtnLabel, &ui_font_heiti22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_ExitBtnLabel);

    lv_obj_add_event_cb(ui_ExitBtn, exit_btn_event_cb, LV_EVENT_ALL, NULL);
    lv_scr_load_anim(echo_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);

    // 启动第一次眨眼（2秒后）
    blink_timer = lv_timer_create(blink_timer_cb, 2000, NULL);
    lv_timer_set_repeat_count(blink_timer, 1);
}

void flower_echo_page_deinit(void) 
{
    // 页面退出时清理定时器
    if (blink_timer) {
        lv_timer_del(blink_timer);
        blink_timer = NULL;
    }
    is_animating = false;
}