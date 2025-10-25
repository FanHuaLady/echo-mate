# 1. 递归收集所有.c文件（和gui_app的file(GLOB_RECURSE)一致）
file(GLOB_RECURSE FLOWER_APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 2. 生成静态库（和gui_app一样用STATIC）
add_library(flower_app STATIC ${FLOWER_APP_SOURCES})

# 3. 暴露头文件路径（PUBLIC让主程序能包含，对齐gui_app）
target_include_directories(flower_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  # flower_ui.h所在目录
    ${CMAKE_CURRENT_SOURCE_DIR}/pages  # 若有子页面，添加此路径
)

# 4. 链接必要依赖（参考gui_app链接json-c、CURL的方式）
# 若用到common模块的函数（如gpio、sys_manager），添加以下依赖
target_link_libraries(flower_app PRIVATE common)
