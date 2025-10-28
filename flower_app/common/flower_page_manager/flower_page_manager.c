#include "flower_page_manager.h"

#include <string.h>

// 页面列表（最多支持10个页面，可根据需求扩展）
#define MAX_PAGE_NUM 10
static flower_lib_pm_page_t *g_page_list[MAX_PAGE_NUM] = {0};               // 页面指针数组
static int g_page_count = 0;

// 全局变量：当前活跃页面
flower_lib_pm_page_t *g_current_page = NULL;

// 注册页面到管理列表
void flower_pm_register_page(flower_lib_pm_page_t *page) 
{
    if (g_page_count >= MAX_PAGE_NUM || page == NULL) return;
    g_page_list[g_page_count++] = page;
}

// 查找页面（通过名称）
static flower_lib_pm_page_t* _find_page(const char *name) 
{
    for (int i = 0; i < g_page_count; i++) 
    {
        if (strcmp(g_page_list[i]->name, name) == 0) 
        {
            return g_page_list[i];
        }
    }
    return NULL;
}

// 页面切换：核心逻辑
void flower_pm_switch_page(const char *page_name) 
{
    flower_lib_pm_page_t *target_page = _find_page(page_name);             // 查找目标页面
    if (target_page == NULL) return;

    // 销毁当前页面
    if (g_current_page != NULL && g_current_page->deinit != NULL) 
    {
        g_current_page->deinit(g_current_page->page_obj);
        lv_obj_del(g_current_page->page_obj);                               // 删除页面对象
    }

    // 初始化目标页面
    lv_obj_t *parent = lv_scr_act();                                        // 父容器为当前屏幕
    target_page->page_obj = lv_obj_create(parent);
    lv_obj_set_size(target_page->page_obj, 320, 240);                       // 屏幕尺寸
    lv_obj_clear_flag(target_page->page_obj, LV_OBJ_FLAG_SCROLLABLE);       // 禁止滚动
    if (target_page->init != NULL) 
    {
        target_page->init(target_page->page_obj);
    }

    g_current_page = target_page;
}