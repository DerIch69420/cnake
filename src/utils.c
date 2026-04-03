/*
 * src/utils.c
 */

#include <ncurses.h>

#include "utils.h"

void init_cnake() {
  initscr();
  keypad(stdscr, TRUE); // Enable keypad
  noecho();             // Don't echo input
  curs_set(0);          // Hide cursor

  if (!has_colors()) {
    printw("Your terminal does not support colors!");
    getch();
    endwin();
  }
  start_color(); // Enable colors

  init_pair(1, COLOR_RED, COLOR_BLACK); // Red text on black background
}
