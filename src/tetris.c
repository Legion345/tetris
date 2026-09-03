/*************************************************
 *
 * 	@file		tetris.c
 *
 * 	@author		Harel Asaraf
 *
 * 	@date		Created Monday, August 17, 2026
 *
 * 	@brief		Main program for tetris
 *
 *
 ************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tetris.h"

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

/************************************************
 *
 *
 *
 *              Array Definitions
 *
 *
 *
 * *********************************************/

tetris_location TETROMINOS[NUM_TETROMINOS][NUM_ORIENTATION][TETRIS] = {
    // I
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
     {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
     {{0, 1}, {1, 1}, {2, 1}, {3, 1}}},
    // J
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {1, 1}, {2, 0}, {2, 1}}},
    // L
    {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
    // O
    {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}}},
    // S
    {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
     {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
    // T
    {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 1}}},
    // Z
    {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 0}}},
};

int GRAVITY_LEVEL[MAX_LEVEL + 1] = {
    // 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    50, 48, 46, 44, 42, 40, 38, 36, 34, 32,
    // 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    30, 28, 26, 24, 22, 20, 16, 12, 8, 4};

/************************************************
 *
 *
 *
 *         Helper Functions for Blocks
 *
 *
 *
 * *********************************************/

// Return the block at the given row and column
char tg_get(tetris_game *obj, int row, int column) {
  return obj->board[obj->cols * row + column];
}

// Set the block at the given rown and column
static void tg_set(tetris_game *obj, int row, int column, char value) {
  obj->board[obj->cols * row + column] = value;
}

// Check whether a row and column are in bounds
bool tg_check(tetris_game *obj, int row, int column) {
  return 0 <= row && row < obj->rows && 0 <= col && col < obj->cols;
}

// Place block onto the board
static void tg_put(tetris_game *obj, tetris_block block) {
  int i;
  for (i = 0; i < TETRIS; i++) {
    tetris_location cell = TETROMINOS[block.typ][block.ori][i];
    tg_set(obj, block.loc.row + cell.row, block.loc.col + cell.col, TC_EMPTY);
  }
}

// Check if a block can be placed on the board
static bool tg_fits(tetris_game *obj, tetris_block block) {
  int i, r, c;
  for (i = 0; i < TETRIS; i++) {
    tetris_location cell = TETROMINOS[block.typ][block.ori][i];
    r = block.loc.row + cell.row;
    c = block.loc.col + cell.col;
    if (!tg_check(obj, r, c) || TC_IS_FILLED(tg_get(obj, r, c))) {
      return false;
    }
  }
  return true;
}

// Return a random tetromino type
static int random_tetromino(void) { return rand() % NUM_TETROMINOS; }

// Create a new falling block and populate the next falling block with a random
// one
static void tg_new_falling(tetris_game *obj) {
  // Put in a new falling tetromino
  obj->falling = obj->next;
  obj->next.typ = random_tetromino();
  obj->next.ori = 0;
  obj->next.loc.row = 0;
  obj->next.loc.col = obj->cols / 2 - 2;
}
