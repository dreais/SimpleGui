//
// Created by Valentin on 11/14/2019.
//

#ifndef SIMPLEGUI_SIMPLE_GUI_H
#define SIMPLEGUI_SIMPLE_GUI_H

#include <ncurses.h>

///		INIT FOLDER
/**                 **\
 *  RETURN VALUES    *
\**                 **/
#define INSTANCE_CREATED 0

typedef struct {
	WINDOW **win;
	unsigned short win_count;
	char inter_buffer[512];
	FILE *stream;
	int z_index;
} instance;

/**                 **\
 *  PROTOTYPES    	 *
\**                 **/

/**
 * create a new instance
 * @param prev_z_index if any, the z-index of the previous instance
 * @return a newly created instance
 */
instance create_instance(int prev_z_index);

/**
 * create and initialize terminal using the below masks
 * @param args a binary mask
 * @param win ptr to the window to apply modification, if any
 * @return 0 if successful, otherwise 1
 */
int create_terminal(unsigned int args, WINDOW *win);

/**                 **\
 *  MASK    	 	 *
\**                 **/
typedef struct {
	unsigned long MASK;
	char *NAME;
	// we need both for functions like keypad()
	int (*func_int)();
	int (*func_win)(WINDOW *, bool bf);
	int func_type;
} MASK_ASSOC;

#define FUNC_INT 1
#define FUNC_WIN 2

#define RAW 	1				// 1
#define CBREAK	RAW << 1		// 10
#define ECHO	CBREAK << 1		// 100
#define NOECHO	ECHO << 1		// 1000
#define KEYPAD	NOECHO << 1		// 10000
#define NOCBREAK KEYPAD << 1	// 100000

#include "easylogs.h"
#include "create_entities.h"

#endif //SIMPLEGUI_SIMPLE_GUI_H
