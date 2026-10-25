cmake_minimum_required(VERSION 3.20)
project(Minesweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找三个 SDL3 相关包，CONFIG 模式使用官方提供的配置文件
find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

# 收集源文件
set(SOURCES
    src/Main.cpp
    src/Application.cpp
    src/Compose.cpp
    src/Game.cpp
    src/Source.cpp
)

add_executable(Minesweeper ${SOURCES})

# 链接库
target_link_libraries(Minesweeper PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
)

# 头文件搜索路径
target_include_directories(Minesweeper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 构建后把 assets/res 复制到可执行文件同级目录的 res/，
# 保持源码中 "res/xxx.png" 的相对路径不变，保证运行时可加载资源
add_custom_command(TARGET Minesweeper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/res
        $<TARGET_FILE_DIR:Minesweeper>/res
)
