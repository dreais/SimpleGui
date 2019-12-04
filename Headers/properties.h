//
// Created by rudreais on 04/12/2019.
//

#ifndef SIMPLEGUI_PROPERTIES_H
#define SIMPLEGUI_PROPERTIES_H

#include <stdbool.h>
#include "simple_gui.h"

typedef struct {
	int x;
	int y;
} pt;

typedef struct {
	pt top_left;
	pt top_right;
	pt bottom_left;
	pt bottom_right;
} pos_t;

bool is_in_window(WINDOW *win, pt coord);
bool non_empty_prop(prop_t *prop);

#endif //SIMPLEGUI_PROPERTIES_H
