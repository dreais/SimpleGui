//
// Created by Valentin on 11/14/2019.
//

#ifndef SIMPLEGUI_SIMPLE_GUI_H
#define SIMPLEGUI_SIMPLE_GUI_H

#include <ncurses.h>

// TODO: use 2 pt types instead of 4 ints
typedef struct {
	int sizx;
	int sizy;
	int posx;
	int posy;
} prop_t;

typedef struct {
	WINDOW **win;
	char **name;
	unsigned short win_count;
	char inter_buffer[512];
	FILE *stream;
	int z_index;
	prop_t properties;
} instance;

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

/**                 **\
 *  MASK    	 	 *
\**                 **/
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

#include "easylogs.h"
#include "create_entities.h"

#endif //SIMPLEGUI_SIMPLE_GUI_H
