//
// Created by Valentin on 11/14/2019.
//

#ifndef SIMPLEGUI_SIMPLE_GUI_H
#define SIMPLEGUI_SIMPLE_GUI_H

#include <ncurses.h>
#include "instance.h"
#include "Modules/buffer.h"

/**
 * create a new instance
 * @param prev_z_index if any, the z-index of the previous instance
 * @return a newly created instance
 */
instance create_instance(int prev_z_index);

/**
 * create and initialize terminal using the below masks
 * @param args a binary mask
 * @return 0 if successful, otherwise 1
 */
int create_terminal(unsigned int args);

/**
 * create and add a new window to an instance
 * @param current the instance we're adding a window to
 * @param properties_window the properties of the new window. if none, will automatically generate
 */
void inst_add_window(instance *current, prop_t *properties_window);

/**
 * create a new window by splitting the previous one in half, using a splitting mode defined
 * @param current the instance we're adding a window to
 * @param g_mode
 * @param set_global
 */
void inst_split_win(instance *current, unsigned short g_mode, bool set_global);

/**
 * pop out a window from within the instance
 * @param current the instance we're removing a window from
 * @param index
 */
void win_pop(instance *current, int index);

typedef struct {
	unsigned long MASK;
	char *NAME;
	// we need the 3 for functions like keypad() or curs_set()
	int (*func_int)();
	int (*func_win)(WINDOW *, bool bf);
	int (*func_int_int)(int);
	int func_type;
} MASK_ASSOC;

#define FUNC_INT 1
#define FUNC_WIN 2
#define FUNC_INT_INT 3

#define RAW 	1u				// 1
#define CBREAK	RAW << 1u		// 10
#define ECHO	CBREAK << 1u		// 100
#define NOECHO	ECHO << 1u		// 1000
#define KEYPAD	NOECHO << 1u		// 10000
#define NOCBREAK KEYPAD << 1u	// 100000
#define NOCURSOR NOCBREAK << 1u	// 1000000

#define INST_ADDED 0		// instance window was added
#define INST_N_ADDED 1		// instance window was NOT added

#include "easylogs.h"
#include "create_entities.h"

#endif //SIMPLEGUI_SIMPLE_GUI_H
