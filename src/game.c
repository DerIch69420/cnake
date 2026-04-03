/*
 * src/game.
 */

#include <ncurses.h>

#include "game.h"

void _setup(int x, int y);
void _tick(int x, int y, int key);

void run_cnake() {
  int x, y, key;

  x = START_X;
  y = START_Y;
  _setup(x, y);

  _tick(x, y, key);
}

void _setup(int x, int y) {

  clear();

  move(y, x);
  attron(COLOR_PAIR(1));
  printw("%c", PLAYER_HEAD);
  attroff(COLOR_PAIR(1));
  refresh();
}

void _tick(int x, int y, int key) {

  while ((key = getch()) != 'q') {

    if (key == KEY_LEFT) {
      // Move to the left
      x--;
      if (x < X_MIN) {
        x = X_MIN;
      }
    } else if (key == KEY_RIGHT) {
      // Move to the right
      x++;
      if (x > X_MAX) {
        x = X_MAX;
      }
    } else if (key == KEY_UP) {
      // Move upwards
      y--;
      if (y < Y_MIN) {
        y = Y_MIN;
      }
    } else if (key == KEY_DOWN) {
      // Move downwards
      y++;
      if (y > Y_MAX) {
        y = Y_MAX;
      }
    }

    clear();

    move(y, x);
    attron(COLOR_PAIR(1));
    printw("%c", PLAYER_HEAD);
    attroff(COLOR_PAIR(1));
    refresh();
  }
}
