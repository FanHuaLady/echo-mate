# 递归收集所有.c文件（包括common和pages子目录）
# 1、GLOB_RECURSE：递归查找
# 2、CMAKE_CURRENT_SOURCE_DIR：当前CMakeLists.txt所在目录
# 3、FLOWER_APP_SOURCES：变量名，存储查找到的源文件列表
file(GLOB_RECURSE FLOWER_APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pages/*/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/images/*.c"
)

# 生成静态库
# 1、flower_app：库名称
# 2、STATIC：库类型（静态库）
# 3、FLOWER_APP_SOURCES：源文件列表
add_library(flower_app STATIC ${FLOWER_APP_SOURCES})

# 暴露头文件路径
# 1、PUBLIC：表示这些路径对使用该库的目标也是可见的
target_include_directories(flower_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/pages
    ${CMAKE_CURRENT_SOURCE_DIR}/images
)

find_package(json-c REQUIRED)
find_package(CURL REQUIRED)

target_link_libraries(flower_app PRIVATE json-c)
target_include_directories(flower_app PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(flower_app PRIVATE CURL::libcurl)
# 链接依赖（若用到common模块）
# 1、PRIVATE：表示这些路径仅对该库可见
target_link_libraries(flower_app PRIVATE common)