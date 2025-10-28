#include "flower_page_manager.h"
#include <string.h>
#include <stdio.h>

// 页面列表（最多支持10个页面，可根据需求扩展）
#define MAX_PAGE_NUM 10
static flower_lib_pm_page_t *g_page_list[MAX_PAGE_NUM] = {0};               // 页面指针数组
static int g_page_count = 0;

// 全局变量：当前活跃页面
flower_lib_pm_page_t *g_current_page = NULL;

// 注册页面到管理列表
void flower_pm_register_page(flower_lib_pm_page_t *page) 
{
    if (g_page_count >= MAX_PAGE_NUM || page == NULL) return;               // 超出最大页面数或页面为空则返回
    g_page_list[g_page_count++] = page;                                     // 添加页面到列表并增加计数
}

// 查找页面（通过名称）
static flower_lib_pm_page_t* _find_page(const char *name) 
{
    for (int i = 0; i < g_page_count; i++)                                  // 遍历已注册页面
    {
        if (strcmp(g_page_list[i]->name, name) == 0)                        // 名称匹配
        {
            printf("Found page: %s\n", name);   
            return g_page_list[i];                                          // 返回匹配的页面指针
        }
    }
    return NULL;
}

// 页面切换：核心逻辑
void flower_pm_switch_page(const char *page_name) 
{
    flower_lib_pm_page_t *target_page = _find_page(page_name);
    if (target_page == NULL) {
        printf("Page not found: %s\n", page_name);
        return;
    }

    printf("Switching to page: %s\n", page_name);

    // 如果目标页面已经是当前页面，直接返回
    if (g_current_page == target_page) {
        printf("Page is already active: %s\n", page_name);
        return;
    }

    // 销毁当前页面
    if (g_current_page != NULL) 
    {
        if (g_current_page->deinit != NULL) {
            g_current_page->deinit(g_current_page->page_obj);
        }
        if (g_current_page->page_obj != NULL) {
            lv_obj_del(g_current_page->page_obj);
            g_current_page->page_obj = NULL;
        }
    }

    // 创建并初始化新页面
    lv_obj_t *parent = lv_scr_act();
    lv_obj_t *new_page = lv_obj_create(parent);
    lv_obj_set_size(new_page, lv_obj_get_width(parent), lv_obj_get_height(parent));
    lv_obj_clear_flag(new_page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(new_page, 0, 0);
    
    target_page->page_obj = new_page;
    
    if (target_page->init != NULL) {
        target_page->init(new_page);
    }

    g_current_page = target_page;
    printf("Successfully switched to page: %s\n", page_name);
}