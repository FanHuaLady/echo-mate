#ifndef _FLOWER_PAGE_MANAGER_H
#define _FLOWER_PAGE_MANAGER_H

#include "../../lvgl/lvgl.h"

// 定义页面结构体
typedef struct {
    char *name;                                     // 页面名称
    void (*init)(lv_obj_t *page);                   // 页面初始化函数
    void (*deinit)(lv_obj_t *page);                 // 页面销毁函数
    lv_obj_t *page_obj;                             // 页面上的主要 LVGL 对象
} flower_lib_pm_page_t;

// IMAGES AND IMAGE SETS
LV_IMG_DECLARE(ui_img_weather64_png);    // assets/weather64.png
LV_IMG_DECLARE(ui_img_calendar64_png);    // assets/calendar64.png
LV_IMG_DECLARE(ui_img_memo64_png);    // assets/Memo64.png
LV_IMG_DECLARE(ui_img_gamememory64_png);    // assets/GameMemory64.png
LV_IMG_DECLARE(ui_img_paint60_png);    // assets/paint60.png
LV_IMG_DECLARE(ui_img_question60_png);    // assets/question60.png
LV_IMG_DECLARE(ui_img_think60_png);    // assets/think60.png
LV_IMG_DECLARE(ui_img_hand60_png);    // assets/hand60.png
LV_IMG_DECLARE(ui_img_muyu128_png);    // assets/muyu128.png
LV_IMG_DECLARE(ui_img_sun_png);    // assets/sun.png
LV_IMG_DECLARE(ui_img_clouds_png);    // assets/clouds.png

// FONTS
LV_FONT_DECLARE(ui_font_iconfont20);
LV_FONT_DECLARE(ui_font_iconfont26);
LV_FONT_DECLARE(ui_font_iconfont30);
LV_FONT_DECLARE(ui_font_iconfont36);
LV_FONT_DECLARE(ui_font_iconfont44);
LV_FONT_DECLARE(ui_font_iconfont48);
LV_FONT_DECLARE(ui_font_heiti14);
LV_FONT_DECLARE(ui_font_heiti22);
LV_FONT_DECLARE(ui_font_heiti24);
LV_FONT_DECLARE(ui_font_shuhei22);
LV_FONT_DECLARE(ui_font_NuberBig90);

void flower_pm_register_page(flower_lib_pm_page_t *page);
void flower_pm_switch_page(const char *page_name);

#endif
