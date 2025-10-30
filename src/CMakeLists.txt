file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/components/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/systems/*.h"
)

add_executable(flappybirddca)

add_custom_command(TARGET flappybirddca POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:flappybirddca>/assets)

install(TARGETS flappybirddca RUNTIME DESTINATION bin)
install(DIRECTORY ${ASSETS_DIR} DESTINATION bin)

target_sources(flappybirddca PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_include_directories(flappybirddca PRIVATE components systems)
target_include_directories(flappybirddca PRIVATE "${CMAKE_SOURCE_DIR}/src/" "${CMAKE_SOURCE_DIR}/src/systems" "${CMAKE_SOURCE_DIR}/src/components")
target_include_directories(flappybirddca PRIVATE "${CMAKE_SOURCE_DIR}/vendor/include/")
target_link_libraries(flappybirddca PRIVATE raylib)
target_link_directories(flappybirddca PRIVATE "${CMAKE_SOURCE_DIR}/vendor/lib")
