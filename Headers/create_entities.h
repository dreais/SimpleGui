//
// Created by rudreais on 02/12/2019.
//

#ifndef SIMPLEGUI_CREATE_ENTITIES_H
#define SIMPLEGUI_CREATE_ENTITIES_H

#include "simple_gui.h"

/**                 **\
 *  PROTOTYPES    	 *
\**                 **/

void win_push_back(instance *current, WINDOW *to_push);
void inst_add_window(instance *current, prop_t *properties_window);

void destroy_win_arr(instance *to_free);

#endif //SIMPLEGUI_CREATE_ENTITIES_H
