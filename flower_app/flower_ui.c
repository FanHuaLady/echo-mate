#include "flower_ui.h"
#include "../../common/gpio_manager/gpio_manager.h"
#include "common/flower_page_manager/flower_page_manager.h"

#include "pages/flower_home_page/flower_home_page.h"
#include "pages/flower_led_page/flower_led_page.h"
#include "pages/flower_weather_page/flower_weather_page.h"

flower_lib_pm_page_t g_home_page[3] = 
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
    },
    {
        .name = "WeatherPage",
        .init = flower_weather_page_init,
        .deinit = flower_weather_page_deinit,
        .page_obj = NULL
    }
};

void LED_Init(void)
{
    gpio_init(LED_BLUE, OUT_DIRECTION);
}

void LED_Loop(void)
{
    static uint16_t time_count = 299;
    time_count++;
    // 每秒闪烁一次LED
    if(time_count % 2 == 0)
    {
        gpio_set_value(LED_BLUE, 1);
    }
    else
    {
        gpio_set_value(LED_BLUE, 0);
    }
}

// 核心初始化函数（对齐ui_init的结构）
void flower_ui_init(void) 
{
    LED_Init();

    flower_pm_register_page(&g_home_page[0]);                              // 注册首页
    flower_pm_register_page(&g_home_page[1]);                              // 注册LED页面
    flower_pm_register_page(&g_home_page[2]);                              // 注册

    lv_timer_create(LED_Loop, 1000, NULL);
    
    flower_pm_switch_page("HomePage");                                     // 切换到首页
}
