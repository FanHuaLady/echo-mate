#ifndef FLOWER_UI_H
#define FLOWER_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../lvgl/lvgl.h"                                           // 直接包含LVGL头文件

// 屏幕尺寸
#define FLOWER_SCREEN_WIDTH 320
#define FLOWER_SCREEN_HEIGHT 240

void flower_ui_init(void);                                          // 核心初始化函数   

// （可选）声明消息框等公共函数，参考gui_app的ui_msgbox_info
void flower_msgbox_info(const char *title, const char *text);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
