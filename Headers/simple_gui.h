//
// Created by Valentin on 11/14/2019.
//

#ifndef SIMPLEGUI_SIMPLE_GUI_H
#define SIMPLEGUI_SIMPLE_GUI_H

#include <ncurses.h>
#include "easylogs.h"

///		INIT FOLDER
/**                 **\
 *  RETURN VALUES    *
\**                 **/
#define INSTANCE_CREATED 0

/**                 **\
 *  PROTOTYPES    	 *
\**                 **/
int create_instance();

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

#endif //SIMPLEGUI_SIMPLE_GUI_H
