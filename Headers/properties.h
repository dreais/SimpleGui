//
// Created by rudreais on 04/12/2019.
//

#ifndef SIMPLEGUI_PROPERTIES_H
#define SIMPLEGUI_PROPERTIES_H

#include <stdbool.h>
#include <instance.h>

bool is_in_window(WINDOW *win, pt coord);
bool is_in_any_window(WINDOW **win, pt coord, unsigned short win_count);
bool non_empty_prop(prop_t *prop);

/**
 * COLORS DEFINITION
 * first define is the COLOR_PAIR key
 * second define is the index from the converted table (see "Sources" in the README)
 */
#define BLANK 0
#define GREEN 1
#define YELLOW 2
#define WHITE 3
#define DARK_GREEN 4
#define LIGHT_GREEN 5
#define GREY 6
#define BROWN 7
#define RED 8

#define RED_BG 9
#define GREY_BG 10

#endif //SIMPLEGUI_PROPERTIES_H
