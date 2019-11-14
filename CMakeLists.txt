cmake_minimum_required(VERSION 3.15)
project(SimpleGui C)

set(CMAKE_C_STANDARD 11)

add_executable(SimpleGui Sources/main.c Headers/simple_gui.h)
target_link_libraries(SimpleGui ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/pdcurses.a)