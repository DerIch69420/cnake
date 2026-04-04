/*
 * src/game.c
 */

#include <ncurses.h>

#include "game.h"

void _setup(int x, int y);
void _tick(int x, int y, int key);

void _draw_borders();

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
    addch(PLAYER_HEAD);
    attroff(COLOR_PAIR(1));

    _draw_borders();
    refresh();
  }
}

void _draw_borders() {
  // Horizontal bars
  for (int i = X_MIN; i <= X_MAX; i++) {
    mvaddch(Y_MIN - 1, i, ACS_HLINE);
    mvaddch(Y_MAX + 1, i, ACS_HLINE);
  }

  // Vertical bars
  for (int i = Y_MIN; i <= Y_MAX; i++) {
    mvaddch(i, X_MIN - 1, ACS_VLINE);
    mvaddch(i, X_MAX + 1, ACS_VLINE);
  }

  // Corners
  mvaddch(Y_MIN - 1, X_MIN - 1, ACS_ULCORNER);
  mvaddch(Y_MIN - 1, X_MAX + 1, ACS_URCORNER);
  mvaddch(Y_MAX + 1, X_MIN - 1, ACS_LLCORNER);
  mvaddch(Y_MAX + 1, X_MAX + 1, ACS_LRCORNER);
}
