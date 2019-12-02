cmake_minimum_required(VERSION 3.10)
project(SimpleGui C)

set(CMAKE_C_STANDARD 11)

# adding pre-compiled static library
message(STATUS "Library ligeasylogs located in: ${CMAKE_SOURCE_DIR}/Libraries/libeasylogs.a")
add_library(libeasylogs STATIC IMPORTED)
set_property(TARGET libeasylogs PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Libraries/libeasylogs.a)
include_directories(${CMAKE_SOURCE_DIR}/Headers)

set(SOURCES Sources/main.c)

set(C_FILES ${SOURCES})
message(STATUS "Creating sources from: ${C_FILES}")
add_executable(SimpleGui ${C_FILES})

if (UNIX)
    set(LIBS libeasylogs)
    target_compile_options(SimpleGui PRIVATE -Wall -Wextra -g -O0)
    target_link_libraries(SimpleGui ${LIBS})
endif (UNIX)