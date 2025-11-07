cmake_minimum_required(VERSION 3.16)
project(libbsc-gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(libbsc-gui
    src/main.cpp
    src/gui.cpp
    src/bsc_runner.cpp
)

target_include_directories(libbsc-gui PRIVATE src)

target_link_libraries(libbsc-gui PRIVATE Qt6::Widgets)

if(WIN32)
    set_target_properties(libbsc-gui PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
