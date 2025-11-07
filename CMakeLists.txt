cmake_minimum_required(VERSION 3.16)
project(libbsc-gui LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add source files
add_executable(libbsc-gui
    src/main.cpp
)

# Link Qt6 libraries
target_link_libraries(libbsc-gui PRIVATE Qt6::Widgets)

# Set Windows icon and properties
if(WIN32)
    set_target_properties(libbsc-gui PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
