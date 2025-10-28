#include "flower_ui.h"
#include "common/flower_page_manager/flower_page_manager.h"
#include "pages/flower_home_page/flower_home_page.h"

flower_lib_pm_page_t g_home_page = 
{
    .name = "HomePage",
    .init = flower_home_page_init,
    .deinit = flower_home_page_deinit,
    .page_obj = NULL
};

// 核心初始化函数（对齐ui_init的结构）
void flower_ui_init(void) 
{
    flower_pm_register_page(&g_home_page);                              // 注册首页
    flower_pm_switch_page("HomePage");                                  // 切换到首页
}
