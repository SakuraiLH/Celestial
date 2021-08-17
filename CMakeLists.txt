# CMake 版本要求 (最低 3.1)
cmake_minimum_required (VERSION 3.1)
# 项目名称（建议修改）
project(Celestial)
# 设置项目的 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 不要构建 mirai-cpp 自带的 examples
set(MIRAI_CPP_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
# 添加子模块 mirai-cpp
add_subdirectory(mirai-cpp)

# 源码以 UTF-8 编码保存，使用 MSVC 编译器时需要加编译参数提供支持
if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    message(STATUS "optional: /UTF-8")   
endif(MSVC)

# 要添加.cpp源文件，请修改这一行
# 例如：add_executable(${PROJECT_NAME} src/main.cpp src/a.cpp src/b.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)
# 设置头文件目录
include_directories(include)
# 链接 mirai-cpp
target_link_libraries(${PROJECT_NAME} PRIVATE mirai-cpp)
# 使用 mirai-cpp 静态库
target_compile_definitions(${PROJECT_NAME} PRIVATE MIRAICPP_STATICLIB)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # 链接 pthread
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
    # 静态链接 libgcc 和 libstdc++
    target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()
