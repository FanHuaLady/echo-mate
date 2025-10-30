#ifndef FLOWER_TIME_MANAGER_H
#define FLOWER_TIME_MANAGER_H

#include <time.h>

// 时间初始化函数
int flower_time_init(void);

// 获取当前时间信息
struct tm *flower_time_get_local_time(void);

// 手动设置系统时间
int flower_time_set_system_time(time_t new_time);

// 从NTP服务器同步时间
int flower_time_sync_from_ntp(void);

// 获取时间同步状态
int flower_time_is_synced(void);

// 清理资源
void flower_time_deinit(void);

#endif
