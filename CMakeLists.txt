cmake_minimum_required(VERSION 3.3)
project(ExplorerRobot1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(lib/Utility/libsimpletools lib/Robotics/ActivityBot/libabdrive)

set(SOURCE_FILES main.c main.h solver.c solver.h)
add_executable(ExplorerRobot1 ${SOURCE_FILES})