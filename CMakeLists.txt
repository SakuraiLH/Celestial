cmake_minimum_required (VERSION 3.1)
project (Celestial)
set (CMAKE_CXX_STANDARD 17)

set(MIRAI_CPP_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
add_subdirectory(mirai-cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
include_directories(include)

target_link_libraries(${PROJECT_NAME} PRIVATE mirai-cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE MIRAICPP_STATICLIB)

find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(foo PRIVATE nlohmann_json::nlohmann_json)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
    target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()