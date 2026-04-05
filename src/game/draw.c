/*
 * src/game/draw.c
 */

#include <ncurses.h>

#include "../game.h"
#include "draw.h"

static void _draw_snake(SnakeNode *head);
static void _draw_food(Food *food);
static void _draw_borders();

void draw_game(SnakeNode *head, Food *food) {
  _draw_borders();
  _draw_snake(head);
  _draw_food(food);
}

static void _draw_snake(SnakeNode *head) {
  // Draw body
  SnakeNode *body = head;
  while ((body = get_next(body))) {
    mvaddch(body->y, body->x, PLAYER_TAIL);
  }

  // Draw head
  attron(COLOR_PAIR(1));
  mvaddch(head->y, head->x, PLAYER_HEAD);
  attroff(COLOR_PAIR(1));
}

static void _draw_food(Food *food) {
  attron(COLOR_PAIR(2));
  mvaddch(food->y, food->x, FOOD);
  attroff(COLOR_PAIR(2));
}

static void _draw_borders() {
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
