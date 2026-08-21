/************************************************
 *
 * 	@file		tetris.h
 *
 * 	@author		Harel Asaraf
 *
 * 	@date		Created Monday, August 17, 2026
 *
 * 	@brief		Main program for tetris
 *
 *
 ************************************************/

#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h> // for bool
#include <stdio.h>   // for FILE

// Convert tetromino type to its corresponding cell
#define TYPE_TO_CELL(x) ((x) + 1)

// Strings for how you would print a tetris board
#define TC_EMPTY_STR " "
#define TC_BLOCK_STR "\u2588"

// Questions about a tetris cell
#define TC_EMPTY_STR(x) ((x) == TC_EMPTY)
#define TC_BLOCK_STR(x) (!TC_IS_EMPTY(x))

// How many cells to a tetromino?
#define TETRIS 4

// How many tetromino?
#define NUM_TETROMINOS 7

// How many orientations of a tetromino?
#define NUM_ORIENTATION 4

// Level constants
#define MAX_LEVEL 19
#define LINES_PER_LEVEL 10

// A "cell" is a 1x1 block within a tetris board
typedef enum {
  TC_EMPTY,
  TC_CELLI,
  TC_CELLJ,
  TC_CELLL,
  TC_CELLO,
  TC_CELLS,
  TC_CELLT,
  TC_CELLZ
} tetris_cell;

// A "type" is a type/shape of a tetromino. Not including orientation
typedef enum { TET_I, TET_J, TET_L, TET_O, TET_S, TET_T, TET_Z } tetris_type;

// A row, column pair. Negative numbers allowed because needed for offsets
typedef struct {
  int row;
  int col;
} tetris_location;

// A "block" is a struct that contains information about a tetromino
// Specfically, what type it is, what orientation it has, and where it is
typedef struct {
  int type;
  int orientation;
  tetris_location loc;
} tetris_block;

// All possible moves to give as input to the game
typedef enum {
  TM_LEFT,
  TM_RIGHT,
  TM_CLOCK,
  TM_COUNTER,
  TM_DROP,
  TM_HOLD,
  TM_NONE
} tetris_move;

// A game object
typedef struct {
  // Game board stuff
  int rows;
  int cols;
  char *board;

  // Scoring information
  int points;
  int level;

  // Falling block is the one currently going down. Next block is the one that
  // will be falling after this one. Stored is the block that you can swap out
  tetris_block falling;
  tetris_block next;
  tetris_block stored;

  // Number of game ticks until the block will move down
  int ticks_until_gravity;

  // Number of lines until you advance to the next level
  int lines_remaining;
} tetris_game;

/*
  This array stores all necessary information about the cells that are filled by
  each tetromino.  The first index is the type of the tetromino (i.e. shape,
  e.g. I, J, Z, etc.).  The next index is the orientation (0-3).  The final
  array contains 4 tetris_location objects, each mapping to an offset from a
  point on the upper left that is the tetromino "origin".
 */
extern tetris_location TETROMINOS[NUM_TETROMINOS][NUM_ORIENTATION][TETRIS];

// This array tells you how many ticks per gravity by level. Decreases as level
// increases, to add difficulty
extern int GRAVITY_LEVEL[MAX_LEVEL + 1];

// Data structure manipulation
void tg_init(tetris_game *obj, int rows, int cols);
tetris_game *tg_create(int rows, int cols);
void tg_destroy(tetris_game *obj);
void tg_delete(tetris_game *obj);
tetris_game *tg_load(FILE *f);
void tg_save(tetris_game *obj, FILE *f);

// Public methods no related to memory
char tg_get(tetris_game *obj, int row, int col);
bool tg_check(tetris_game *obj, int row, int col);
bool tg_tick(tetris_game *obj, tetris_move move);
void tg_print(tetris_game *obj, FILE *f);

#endif // TETRIS_H
