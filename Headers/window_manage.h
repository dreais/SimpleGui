//
// Created by rudreais on 09/12/2019.
//

#ifndef SIMPLEGUI_WINDOW_MANAGE_H
#define SIMPLEGUI_WINDOW_MANAGE_H

#include "simple_gui.h"

void resize_window(WINDOW *to_resize, prop_t prop);
WINDOW *new_win(prop_t *properties);
void hit_windows(instance *current, prop_t *prop);
prop_t get_start(instance *current);

#define SPLIT_MODE_VERT 1	// split mode is vertical
#define SPLIT_MODE_HORI	2	// split mode is horizontal
#define SPLIT_MODE_DEFAULT SPLIT_MODE_VERT

#endif //SIMPLEGUI_WINDOW_MANAGE_H
