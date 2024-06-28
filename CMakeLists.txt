cmake_minimum_required(VERSION 3.0)
project(HW7)

add_library(HW7 STATIC add.c sub.c mul.c div.c)

add_executable(HW_7 main.c)

target_link_libraries(HW_7 PRIVATE HW7)