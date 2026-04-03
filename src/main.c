/*
 * src/main.c
 * Snake game using ncurses
 */

#include <ncurses.h>

#include "game.h"
#include "utils.h"

int main(void) {
  init_cnake();

  run_cnake();

  endwin();

  return 0;
}
