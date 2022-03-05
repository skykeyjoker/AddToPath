cmake_minimum_required(VERSION 3.21)
project(AddToPath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Core)

add_executable(AddToPath main.cpp UAC.h)

target_link_libraries(AddToPath Qt5::Core)
