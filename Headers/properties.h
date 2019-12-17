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

#endif //SIMPLEGUI_PROPERTIES_H
