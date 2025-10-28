#include "flower_ui.h"
#include "common/flower_page_manager/flower_page_manager.h"
#include "pages/flower_home_page/flower_home_page.h"
#include "pages/flower_led_page/flower_led_page.h"

flower_lib_pm_page_t g_home_page[2] = 
{
    {
        .name = "HomePage",
        .init = flower_home_page_init,
        .deinit = flower_home_page_deinit,
        .page_obj = NULL
    },
    {
        .name = "LEDPage",
        .init = flower_led_page_init,
        .deinit = flower_led_page_deinit,
        .page_obj = NULL
    }
};

// 核心初始化函数（对齐ui_init的结构）
void flower_ui_init(void) 
{
    flower_pm_register_page(&g_home_page[0]);                              // 注册首页
    flower_pm_register_page(&g_home_page[1]);                              // 注册LED页面
    flower_pm_switch_page("HomePage");                                     // 切换到首页
}
