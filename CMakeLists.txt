cmake_minimum_required(VERSION 3.0)
project(HW8)

add_library(HW8 SHARED add.c sub.c mul.c div.c)

add_executable(HW_8 main.c)

target_link_libraries(HW_8 PRIVATE HW8)