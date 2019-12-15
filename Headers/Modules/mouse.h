//
// Created by rudreais on 15/12/2019.
//

#ifndef SIMPLEGUI_MOUSE_H
#define SIMPLEGUI_MOUSE_H

#include "../simple_gui.h"
#include "../properties.h"

#define NUMTHRDS 1

extern pt coord_found;
extern pthread_mutex_t mutexcoord;

short find_window(instance *current, pt coord);
void cancel_poll(void);
void check_click(instance *current);
void *mouse_events(void *);

#endif //SIMPLEGUI_MOUSE_H
