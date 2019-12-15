cmake_minimum_required(VERSION 3.10)
project(SimpleGui C)

set(CMAKE_C_STANDARD 11)

# adding pre-compiled static library
message(STATUS "Library ligeasylogs located in: ${CMAKE_SOURCE_DIR}/Libraries/libeasylogs.a")
add_library(libeasylogs STATIC IMPORTED)
set_property(TARGET libeasylogs PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Libraries/libeasylogs.a)
include_directories(${CMAKE_SOURCE_DIR}/Headers)

add_library(libncursest STATIC IMPORTED)
set_property(TARGET libncursest PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Libraries/libncursest.a)

set(SOURCES Sources/main.c Sources/Init/create_entities.c Headers/create_entities.h Headers/window_manage.h Sources/Init/init_mask.c Sources/Instances/push_back.c Sources/Instances/delete.c Sources/Instances/window_manage.c Sources/Properties/states.c Headers/properties.h Sources/Windows/Dropdown/dropdown_manage.c Sources/Instances/window_split.c Sources/Instances/windows_add.c Sources/Instances/pop_window.c Headers/Modules/dropdown.h Sources/Windows/Buffer/buffer_actions.c Headers/Modules/buffer.h Sources/Windows/Mouse/mouse_events.c Headers/Modules/mouse.h)

set(C_FILES ${SOURCES})
message(STATUS "Creating sources from: ${C_FILES}")
add_executable(SimpleGui ${C_FILES})

if (UNIX)
    set(LIBS libeasylogs ncurses pthread)
    target_compile_options(SimpleGui PRIVATE -Wall -Wextra -g -O0)
    target_link_libraries(SimpleGui ${LIBS})
endif (UNIX)