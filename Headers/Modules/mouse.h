//
// Created by rudreais on 15/12/2019.
//

#ifndef SIMPLEGUI_MOUSE_H
#define SIMPLEGUI_MOUSE_H

#include "../simple_gui.h"
#include "../properties.h"

#define NUMTHRDS 1

extern volatile pt coord_found;

short find_window(instance *current, pt coord);
void cancel_poll(void);
void click_coord(instance *current);
void *mouse_events(void *);

#endif //SIMPLEGUI_MOUSE_H
