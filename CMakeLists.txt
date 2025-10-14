cmake_minimum_required(VERSION 3.20)

project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SRCS GCONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(game ${SRCS})
target_link_libraries(game PRIVATE raylib)
target_compile_definitions(game PRIVATE PLATFORM_DESKTOP)
target_include_directories(game PRIVATE "${CMAKE_SOURCE_DIR}/src/")
