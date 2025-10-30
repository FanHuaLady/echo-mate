#include "flower_time_manager.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

#define NTP_SERVER "cn.pool.ntp.org"
#define NTP_PORT 123
#define NTP_TIMEOUT 5000  // 5秒超时

// NTP协议时间戳结构 (RFC 5905)
typedef struct {
    uint8_t li_vn_mode;      // 跳跃指示器, 版本号, 模式
    uint8_t stratum;         // 层级
    uint8_t poll;            // 轮询间隔
    uint8_t precision;       // 精度
    uint32_t root_delay;     // 根延迟
    uint32_t root_dispersion; // 根离散
    uint32_t ref_id;         // 参考标识符
    uint32_t ref_ts_sec;     // 参考时间戳秒
    uint32_t ref_ts_frac;    // 参考时间戳分数
    uint32_t orig_ts_sec;    // 起源时间戳秒
    uint32_t orig_ts_frac;   // 起源时间戳分数
    uint32_t recv_ts_sec;    // 接收时间戳秒
    uint32_t recv_ts_frac;   // 接收时间戳分数
    uint32_t trans_ts_sec;   // 传输时间戳秒
    uint32_t trans_ts_frac;  // 传输时间戳分数
} ntp_packet;

static int time_synced = 0;

// 网络字节顺序转换
uint32_t ntohl_uint32(uint32_t netlong) 
{
    return ((netlong & 0xFF) << 24) | 
           ((netlong & 0xFF00) << 8) | 
           ((netlong & 0xFF0000) >> 8) | 
           ((netlong & 0xFF000000) >> 24);
}

int flower_time_init(void) 
{
    printf("Initializing time manager...\n");
    
    // 尝试从NTP同步时间
    if (flower_time_sync_from_ntp() == 0) 
    {
        time_synced = 1;
        printf("Time synchronized successfully from NTP\n");
        return 0;
    }
    
    // 如果NTP同步失败，使用系统当前时间
    printf("NTP sync failed, using system time\n");
    time_synced = 0;
    return -1;
}

int flower_time_sync_from_ntp(void) 
{
    int sockfd;
    struct sockaddr_in server_addr;
    ntp_packet packet = {0};
    time_t current_time;
    struct timeval tv;
    
    // 创建socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) 
    {
        printf("Failed to create socket: %s\n", strerror(errno));
        return -1;
    }
    
    // 设置超时
    tv.tv_sec = NTP_TIMEOUT / 1000;
    tv.tv_usec = (NTP_TIMEOUT % 1000) * 1000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    
    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(NTP_PORT);
    
    if (inet_pton(AF_INET, "120.25.115.20", &server_addr.sin_addr) <= 0) 
    {
        // 如果DNS解析失败，尝试其他NTP服务器
        inet_pton(AF_INET, "203.107.6.88", &server_addr.sin_addr); // 阿里云NTP
    }
    
    // 构造NTP请求包
    packet.li_vn_mode = (0x03 << 3) | 0x03; // 版本3, 客户端模式
    
    // 发送请求
    if (sendto(sockfd, &packet, sizeof(packet), 0, 
               (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        printf("Failed to send NTP request: %s\n", strerror(errno));
        close(sockfd);
        return -1;
    }
    
    // 接收响应
    socklen_t addr_len = sizeof(server_addr);
    ssize_t recv_len = recvfrom(sockfd, &packet, sizeof(packet), 0, 
                               (struct sockaddr *)&server_addr, &addr_len);
    
    if (recv_len < sizeof(packet)) 
    {
        printf("Failed to receive NTP response: %s\n", strerror(errno));
        close(sockfd);
        return -1;
    }
    
    close(sockfd);
    
    // 解析NTP时间 (1900年1月1日到1970年1月1日的秒数差是2208988800)
    uint32_t ntp_seconds = ntohl_uint32(packet.trans_ts_sec);
    current_time = (time_t)(ntp_seconds - 2208988800UL);
    
    // 设置系统时间
    if (flower_time_set_system_time(current_time) == 0) 
    {
        time_synced = 1;
        return 0;
    }
    
    return -1;
}

int flower_time_set_system_time(time_t new_time) 
{
    struct timeval tv;
    
    tv.tv_sec = new_time;
    tv.tv_usec = 0;
    
    if (settimeofday(&tv, NULL) == 0) 
    {
        printf("System time updated successfully\n");
        return 0;
    } 
    else 
    {
        printf("Failed to set system time: %s\n", strerror(errno));
        return -1;
    }
}

struct tm *flower_time_get_local_time(void) {
    static struct tm timeinfo;
    time_t now = time(NULL);
    
    if (localtime_r(&now, &timeinfo) != NULL) {
        return &timeinfo;
    }
    
    return NULL;
}

int flower_time_is_synced(void) 
{
    return time_synced;
}

void flower_time_deinit(void) 
{
    // 目前没有需要清理的资源
    time_synced = 0;
    printf("Time manager deinitialized\n");
}
