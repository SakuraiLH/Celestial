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

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG 67e12da316754ff3c6c91b50aafb2658438f3c1e)
FetchContent_MakeAvailable(cpr)
target_link_libraries(your_target_name PRIVATE cpr::cpr)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
    target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()