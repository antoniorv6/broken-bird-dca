cmake_minimum_required(VERSION 3.15)

project(FlappyBirdDCA VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor")
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

include(Dependencies.cmake)

add_subdirectory(src)

if(EXISTS ${CMAKE_SOURCE_DIR}/CPackConfig.cmake)
    include("${CMAKE_SOURCE_DIR}/CPackConfig.cmake")
endif()

