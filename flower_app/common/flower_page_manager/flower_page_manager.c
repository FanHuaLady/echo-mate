#include "flower_page_manager.h"
#include <string.h>
#include <stdio.h>

// 页面列表（最多支持10个页面，可根据需求扩展）
#define MAX_PAGE_NUM 10
static flower_lib_pm_page_t *g_page_list[MAX_PAGE_NUM] = {0};               // 页面指针数组
static int g_page_count = 0;
flower_lib_pm_page_t *g_current_page = NULL;                                // 当前活动页面指针

// 注册页面到管理列表
void flower_pm_register_page(flower_lib_pm_page_t *page) 
{
    if (g_page_count >= MAX_PAGE_NUM || page == NULL) return;               // 超出最大页面数或页面为空则返回
    g_page_list[g_page_count++] = page;                                     // 添加页面到列表并增加计数
}

// 查找页面（通过名称）
flower_lib_pm_page_t* find_page(const char *name) 
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
    flower_lib_pm_page_t *target_page = find_page(page_name);               // 查找目标页面
    if (target_page == NULL) 
    {
        printf("Page not found: %s\n", page_name);                          // 没有发现目标页面
        return;
    }

    if (g_current_page == target_page)                                      // 如果目标页面已经是当前页面，直接返回
    {
        printf("Page is already active: %s\n", page_name);                  //
        return;
    }
    printf("Switching to page: %s\n", page_name);
    
    // 销毁当前页面
    if (g_current_page != NULL)                                             // 当前界面存在
    {
        printf("Deinitializing current page: %s\n", g_current_page->name);
        if (g_current_page->deinit != NULL)                                 // 此界面存在销毁函数
        {
            printf("Calling deinit for current page: %s\n", g_current_page->name);
            g_current_page->deinit();                                       // 调用当前页面的销毁函数
        }
        if (g_current_page->page_obj != NULL)                               // 当前页面对象存在
        {
            printf("Deleting current page object\n");
            lv_obj_del(g_current_page->page_obj);                           // 删除当前页面对象
            g_current_page->page_obj = NULL;
        }
    }
    
    printf("Initializing target page: %s\n", target_page->name);
    // 初始化新页面
    if (target_page->init != NULL) 
    {
        printf("Calling init for target page: %s\n", target_page->name);
        target_page->init();                                                // 调用新页面的初始化函数    
    }

    g_current_page = target_page;
    printf("Successfully switched to page: %s\n", page_name);
}
