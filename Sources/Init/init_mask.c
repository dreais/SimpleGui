//
// Created by rudreais on 02/12/2019.
//

#include <ncurses.h>
#include "../Headers/simple_gui.h"

static MASK_ASSOC MASKS[] = {
		{.func_int = &raw, .MASK = RAW, .NAME = "RAW", .func_type = FUNC_INT},
		{.func_int = &cbreak, .MASK = CBREAK, .NAME = "CBREAK", .func_type = FUNC_INT},
		{.func_int = &echo, .MASK = ECHO, .NAME = "ECHO", .func_type = FUNC_INT},
		{.func_int = &noecho, .MASK = NOECHO, .NAME = "NOECHO", .func_type = FUNC_INT},
		{.func_win = &keypad, .MASK = KEYPAD, .NAME = "KEYPAD", .func_type = FUNC_WIN},
		{.func_int = &nocbreak, .MASK = NOCBREAK, .NAME="NOCBREAK", .func_type = FUNC_INT}
};

int create_terminal(unsigned int args, WINDOW *win)
{
	unsigned int mask = 0 | args;
	unsigned long size_masks = sizeof(MASKS) / sizeof(MASK_ASSOC);

	initscr();
	for (unsigned int i = 0; i < size_masks; i++) {
		if (mask & MASKS[i].MASK) {
			output_logs_str(PREFIX_DEBUG, "Applying arg %s to the terminal.\n", MASKS[i].NAME);
			if (MASKS[i].func_type == FUNC_INT) {
				MASKS[i].func_int();
			} else if (MASKS[i].func_type == FUNC_WIN) {
				MASKS[i].func_win(win, true);
			}
		}
	}
	return 0;
}