/*
 * src/game.c
 */

#include <ncurses.h>

#include "game.h"
#include "snake.h"

typedef enum {
  NONE,
  QUIT,
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
} PlayerAction;

typedef enum {
  LEFT,
  RIGHT,
  UP,
  DOWN,
} Direction;

static SnakeNode *head;
static SnakeNode *tail;
static int gameRunning = 1;

static void _setup();
static void _tick();

static void _draw_borders();
static void _draw_snake();
static PlayerAction _user_input(int key);
static void _do_action(PlayerAction action);
static void _move(Direction direction);

void run_cnake() {

  _setup();

  _tick();

  free_snake(head);
}

static void _setup() {

  clear();

  head = create_head(START_X, START_Y);
  tail = add_segment(head, START_X - 1, START_Y);
  head = push_head(head, START_X + 1, START_Y);

  _draw_snake();
  _draw_borders();

  refresh();
}

static void _tick() {
  int key;
  PlayerAction action;

  while (gameRunning != 0) {

    action = _user_input((key = getch()));
    _do_action(action);

    clear();

    _draw_snake();
    _draw_borders();
    refresh();
  }
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

static PlayerAction _user_input(int key) {
  // Map user input to corresponding action

  switch (key) {
  case 'q':
    return QUIT;
  case KEY_LEFT:
  case 'a':
    return MOVE_LEFT;
  case KEY_RIGHT:
  case 'd':
    return MOVE_RIGHT;
  case KEY_UP:
  case 'w':
    return MOVE_UP;
  case KEY_DOWN:
  case 's':
    return MOVE_DOWN;
  default:
    return NONE;
  }
}

static void _do_action(PlayerAction action) {
  switch (action) {
  case QUIT:
    gameRunning = 0;
    return;
  case MOVE_LEFT:
    _move(LEFT);
    return;
  case MOVE_RIGHT:
    _move(RIGHT);
    return;
  case MOVE_UP:
    _move(UP);
    return;
  case MOVE_DOWN:
    _move(DOWN);
    return;
  case NONE:
    return;
  }
}

static void _move(Direction direction) {
  switch (direction) {
  case LEFT: {
    head = push_head(head, head->x - 1, head->y);
    if (head->x < X_MIN) {
      head->x = X_MIN;
    }
    break;
  }

  case RIGHT: {
    head = push_head(head, head->x + 1, head->y);
    if (head->x > X_MAX) {
      head->x = X_MAX;
    }
    break;
  }

  case UP: {
    head = push_head(head, head->x, head->y - 1);
    if (head->y < Y_MIN) {
      head->y = Y_MIN;
    }
    break;
  }
  case DOWN: {
    head = push_head(head, head->x, head->y + 1);
    if (head->y > Y_MAX) {
      head->y = Y_MAX;
    }
    break;
  }
  }
  tail = free_tail(tail);
}

static void _draw_snake() {
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
