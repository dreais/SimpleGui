//
// Created by rudreais on 14/12/2019.
//

#ifndef SIMPLEGUI_BUFFER_H
#define SIMPLEGUI_BUFFER_H


/**
 * char **word_arr 	=> array containing words
 * short c_line 	=> short containing current line, used to scroll
 * short c_word		=> short containing word index, used to apply effects if any
 */

typedef struct {
	char **word_arr;
	short c_line;
	short c_word;
} t_buff;

#endif //SIMPLEGUI_BUFFER_H
