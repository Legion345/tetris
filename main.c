/************************************************
 *
 * 	@file		main.c
 *
 * 	@author		Harel Asaraf
 *
 * 	@date		Created Monday, August 17, 2026
 *
 * 	@brief		Main program for tetris
 *
 *
 ************************************************/

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if WITH_SDL
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#endif

#include "tetris.h"
#include "util.h"

/*
 2 columns per cell makes game much nicer
 */
#define COLS_PER_CELL 2

/*
 Macro to print a cell of a specific type to a window
 */
#define ADD_BLOCK(w, x)                                                        \
  waddch((w), ' ' | A_REVERSE | COLOR_PAIR(x));                                \
  waddch((w), ' ' | A_REVERSE | COLOR_PAIR(x))

#define ADD_EMPTY(w)                                                           \
  waddch((w), ' ');                                                            \
  waddch((w), ' ')

/*
Print the tetris board onto the ncurses window
*/
void display_board(WINDOW *w, tetris_game *obj) {
  int i, j;
  box(w, 0, 0);
  for (i = 0; i < obj->rows; i++) {
    wmove(w, 1 + i, 1);
    for (j = 0; j < obj->cols; j++) {
      if (TC_IS_FILLED(tg_get(obj, i, j))) {
        ADD_BLOCK(w, tg_get(obj, i, j));
      } else {
        ADD_EMPTY(w)
      }
    }
  }
  wnoutrefresh(w);
}
