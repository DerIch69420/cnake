/*
 * src/game/draw.c
 */

#include <ncurses.h>

#include "draw.h"

static void _draw_snake(SnakeNode *head);
static void _draw_food(Food *food);
static void _draw_borders();

void draw_game(SnakeNode *head, Food *food) {
  _draw_borders();
  _draw_snake(head);
  _draw_food(food);
}

#ifdef DEBUG
static void _draw_snake(SnakeNode *head) {
  // Draw body
  SnakeNode *body = head;
  int row = 0; // row on top of the screen for debug info
  mvprintw(row, 0, "Snake coords (x,y) and drawn pos:");
  row++;

  int segment_index = 0;
  while ((body = get_next(body))) {
    // Draw body segment
    mvaddch(body->y, body->x, PLAYER_TAIL);
    mvaddch(body->y, body->x + 1, PLAYER_TAIL);

    // Debug info
    mvprintw(row, 0, "Segment %2d: (x=%2d,y=%2d) drawn at y=%2d, x=%2d/%2d",
             segment_index, body->x, body->y, body->y, body->x, body->x + 1);
    row++;
    segment_index++;
  }

  // Draw head
  attron(COLOR_PAIR(1));
  mvaddch(head->y, head->x, PLAYER_HEAD);
  mvaddch(head->y, head->x + 1, PLAYER_HEAD);
  attroff(COLOR_PAIR(1));

  // Debug info for head
  mvprintw(row, 0, "Head: (x=%2d,y=%2d) drawn at y=%2d, x=%2d/%2d", head->x,
           head->y, head->y, head->x, head->x + 1);
}

#else
static void _draw_snake(SnakeNode *head) {
  // Draw body
  SnakeNode *body = head;
  while ((body = get_next(body))) {
    mvaddch(body->y, body->x, PLAYER_TAIL);
    mvaddch(body->y, body->x + 1, PLAYER_TAIL);
  }

  // Draw head
  attron(COLOR_PAIR(1));
  mvaddch(head->y, head->x, PLAYER_HEAD);
  mvaddch(head->y, head->x + 1, PLAYER_HEAD);
  attroff(COLOR_PAIR(1));
}
#endif

static void _draw_food(Food *food) {

  char food_char;

  switch (food->food_type) {
  case FOOD_NORMAL:
    attron(COLOR_PAIR(2)); // Green
    food_char = FOOD_NORMAL_CHAR;
    break;
  case FOOD_DOUBLE:
    attron(COLOR_PAIR(3)); // Magenta
    food_char = FOOD_DOUBLE_CHAR;
    break;
  case FOOD_USELESS:
  default:
    // Use no color pair
    food_char = FOOD_USELESS_CHAR;
    break;
  }

  mvaddch(food->y, food->x, food_char);

  // Turn off the color pair after drawing
  switch (food->food_type) {
  case FOOD_NORMAL:
    attroff(COLOR_PAIR(2));
    break;
  case FOOD_DOUBLE:
    attroff(COLOR_PAIR(3));
    break;
  case FOOD_USELESS:
  default:
    break;
  }
}

static void _draw_borders() {
  // Horizontal bars
  for (int i = X_MIN; i <= X_MAX_TERMINAL; i++) {
    mvaddch(Y_MIN - 1, i, ACS_HLINE);
    mvaddch(Y_MAX + 1, i, ACS_HLINE);
  }

  // Vertical bars
  for (int i = Y_MIN; i <= Y_MAX; i++) {
    mvaddch(i, X_MIN - 1, ACS_VLINE);
    mvaddch(i, X_MAX_TERMINAL + 1, ACS_VLINE);
  }

  // Corners
  mvaddch(Y_MIN - 1, X_MIN - 1, ACS_ULCORNER);
  mvaddch(Y_MIN - 1, X_MAX_TERMINAL + 1, ACS_URCORNER);
  mvaddch(Y_MAX + 1, X_MIN - 1, ACS_LLCORNER);
  mvaddch(Y_MAX + 1, X_MAX_TERMINAL + 1, ACS_LRCORNER);
}
