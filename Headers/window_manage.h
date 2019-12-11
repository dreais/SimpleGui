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


unsigned short fetch_n(instance *current);
unsigned short fetch_n_before(instance *current, int index);
unsigned short fetch_n_after(instance *current, int index);

#define SPLIT_NONE 0		// used for some occasion (see window_manage.c/fetch_n_before())
#define SPLIT_MODE_VERT 1	// split mode is vertical
#define SPLIT_MODE_HORI	2	// split mode is horizontal
#define SPLIT_MODE_DEFAULT SPLIT_MODE_VERT

#define IS_HORI_MODE(w1, w2) (getbegx(w1) == getbegx(w2)) ? SPLIT_MODE_HORI : SPLIT_NONE
#define IS_VERT_MODE(w1, w2)  (getbegy(w1) == getbegy(w2)) ? SPLIT_MODE_VERT : IS_HORI_MODE(w1, w2)
// more dev-friendly way of calling
#define FETCH_MODE(w1, w2) IS_VERT_MODE(w1, w2)

#endif //SIMPLEGUI_WINDOW_MANAGE_H
