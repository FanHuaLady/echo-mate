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

// 定义 PageManager 类型
// 之后实现

#endif
