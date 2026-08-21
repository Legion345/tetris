/************************************************
 *
 * 	@file		util.c
 *
 * 	@author		Harel Asaraf
 *
 * 	@date		Created Monday, August 17, 2026
 *
 * 	@brief		Main program for tetris
 *
 *
 ************************************************/

#define _POSIX_C_SOURCE 199309L

#include <time.h> // nanosleep

void sleep_milli(int milliseconds) {
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = milliseconds * 1000 * 1000;
  nanosleep(&ts, NULL);
}
