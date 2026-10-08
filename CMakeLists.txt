cmake_minimum_required(VERSION 3.22)
project(sfml3-widgets VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.hpp"
    "src/*.h"
)
add_library(sfml3-widgets STATIC ${SRC_FILES})
target_include_directories(sfml3-widgets PUBLIC src)
target_link_libraries(sfml3-widgets PUBLIC GL SFML::Graphics SFML::Window SFML::System)

file(GLOB DEMO_FILES "demo/*.cpp")
add_executable(sfml3-widgets-demo ${DEMO_FILES})
target_include_directories(sfml3-widgets-demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/demo)
target_link_libraries(sfml3-widgets-demo PRIVATE sfml3-widgets)

add_custom_command(TARGET sfml3-widgets-demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/demo"
    "$<TARGET_FILE_DIR:sfml3-widgets-demo>/demo"
    COMMENT "Copying assets to build directory..."
)
