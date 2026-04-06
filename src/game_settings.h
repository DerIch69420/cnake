/*
 * src/game_settings.h
 */

#pragma once

/* Map size */
#define X_MIN 1
// This is the max of the terminal, not the max of the map
#define X_MAX_TERMINAL 75
#define X_MAX (X_MAX_TERMINAL / 2 - X_MIN)
#define Y_MIN 1
#define Y_MAX 25

/* Player start position. */
#define START_X 5
#define START_Y 5

/* Player characters */
#define PLAYER_HEAD ACS_CKBOARD
#define PLAYER_TAIL ACS_CKBOARD

/* Food character */
#define FOOD_NORMAL_CHAR 'O'
#define FOOD_USELESS_CHAR 'O'
#define FOOD_DOUBLE_CHAR '@'

/* Game speed */
#define TICKS_PER_SECOND 8
