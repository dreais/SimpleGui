//
// Created by rudreais on 16/12/2019.
//

#ifndef SIMPLEGUI_INSTANCE_H
#define SIMPLEGUI_INSTANCE_H

#include <ncurses.h>

/**
 * char **word_arr 	=> array containing words
 * short c_line 	=> short containing current line, used to scroll
 * short c_word		=> short containing word index, used to apply effects if any
 */

typedef struct {
	int x;
	int y;
} pt;

typedef struct {
	pt top_left;
	pt top_right;
	pt bottom_left;
	pt bottom_right;
} pos_t;

typedef struct {
	int sizx;
	int sizy;
	int posx;
	int posy;
} prop_t;

typedef struct {
	char **word_arr;
	int *properties;
	short scroll_size;
	short c_line;
	short c_word;
} t_buff;

typedef struct {
	WINDOW **win;
	char **name; // unused for now
	t_buff **buffer; // contains char **word_arr
	unsigned short win_count;
	FILE *stream;
	int z_index;
	prop_t properties;
} instance;

void show_win(instance *current);

void w_set_active(pt coord);
short w_get_active(void);
void set_instance(instance *current);

#endif //SIMPLEGUI_INSTANCE_H
