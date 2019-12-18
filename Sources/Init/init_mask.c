//
// Created by rudreais on 02/12/2019.
//

#include <simple_gui.h>
#include <Modules/mouse.h>

static MASK_ASSOC MASKS[] = {
		{.func_int = &raw, .MASK = RAW, .NAME = "RAW", .func_type = FUNC_INT},
		{.func_int = &cbreak, .MASK = CBREAK, .NAME = "CBREAK", .func_type = FUNC_INT},
		{.func_int = &echo, .MASK = ECHO, .NAME = "ECHO", .func_type = FUNC_INT},
		{.func_int = &noecho, .MASK = NOECHO, .NAME = "NOECHO", .func_type = FUNC_INT},
		{.func_win = &keypad, .MASK = KEYPAD, .NAME = "KEYPAD", .func_type = FUNC_WIN},
		{.func_int = &nocbreak, .MASK = NOCBREAK, .NAME="NOCBREAK", .func_type = FUNC_INT},
		{.func_int_int = &curs_set, .MASK = NOCURSOR, .NAME="NOCURSOR", .func_type = FUNC_INT_INT}
};

static void get_colors(void)
{
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(RED_BG, COLOR_RED, COLOR_RED);
}

int create_terminal(unsigned int args)
{
	unsigned int mask = 0u | args;
	unsigned long size_masks = sizeof(MASKS) / sizeof(MASK_ASSOC);

	get_log_file();
	initscr();
	start_color();
	get_colors();
	for (unsigned int i = 0; i < size_masks; i++) {
		if (mask & MASKS[i].MASK) {
			output_logs_str(PREFIX_DEBUG, "Applying arg %s to the terminal.\n", MASKS[i].NAME);
			if (MASKS[i].func_type == FUNC_INT) {
				MASKS[i].func_int();
			} else if (MASKS[i].func_type == FUNC_WIN) {
				MASKS[i].func_win(stdscr, true);
			} else if (MASKS[i].func_type == FUNC_INT_INT) {
				MASKS[i].func_int_int(0);
			}
		}
	}
	return 0;
}