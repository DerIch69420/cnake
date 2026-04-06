/*
 * src/game.c
 */

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "game.h"
#include "game/colliding.h"
#include "game/draw.h"
#include "game/food.h"
#include "game/snake.h"
#include "game_settings.h"

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
  NONE_DIR, // Player won't move in this state
} Direction;

static SnakeNode *head;
static SnakeNode *tail;
static Food *food;
static int gameRunning = 1;
static Direction currentDirection = NONE_DIR;

static void _setup();
static void _tick();

static PlayerAction _user_input(int key);
static void _do_action(PlayerAction action);
static void _move(Direction direction);
static void _collide_with_wall();
static void _collide_with_self();

void run_cnake() {

  _setup();

  _tick();

  free_snake(head);
  free(food);
}

static void _setup() {

  clear();

  head = create_head(START_X, START_Y);
  tail = add_segment(head, head->x - 2, head->y);
  tail = add_segment(tail, tail->x - 2, tail->y);

  food = generate_food(X_MIN, X_MAX, Y_MIN, Y_MAX);

  draw_game(head, food);

  refresh();
}

static void _tick() {
  int key;
  PlayerAction action;

  timeout((1000 / TICKS_PER_SECOND));

  while (gameRunning != 0) {

    action = _user_input((key = getch()));
    _do_action(action);

    _move(currentDirection);

    clear();

    draw_game(head, food);
    refresh();
  }
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
    // No 180 degree turn
    if (currentDirection == RIGHT) {
      return;
    }
    currentDirection = LEFT;
    return;
  case MOVE_RIGHT:
    // No 180 degree turn
    if (currentDirection == LEFT) {
      return;
    }
    currentDirection = RIGHT;
    return;
  case MOVE_UP:
    // No 180 degree turn
    if (currentDirection == DOWN) {
      return;
    }
    currentDirection = UP;
    return;
  case MOVE_DOWN:
    // No 180 degree turn
    if (currentDirection == UP) {
      return;
    }
    currentDirection = DOWN;
    return;
  case NONE:
    return;
  }
}

static void _move(Direction direction) {
  switch (direction) {
  case LEFT: {
    head = push_head(head, head->x - 2, head->y);
    break;
  }

  case RIGHT: {
    head = push_head(head, head->x + 2, head->y);
    break;
  }

  case UP: {
    head = push_head(head, head->x, head->y - 1);
    break;
  }
  case DOWN: {
    head = push_head(head, head->x, head->y + 1);
    break;
  }
  case NONE_DIR: {
    // Do not move or do anything else
    return;
  }
  }

  switch (check_colliding(head)) {
  case COLLIDE_WITH_WALL: {
    _collide_with_wall();
    break;
  }
  case COLLIDE_WITH_SELF: {
    _collide_with_self();
    break;
  }
  case NOT_COLLIDING: {
    break;
  }
  }

  FoodType old_type = food->food_type;
  if (!check_food(head, &food)) {
    tail = free_tail(tail);
  } else {

    switch (old_type) {
    case FOOD_NORMAL: {
      break;
    }
    case FOOD_USELESS: {
      tail = free_tail(tail);
      break;
    }
    case FOOD_DOUBLE: {
      switch (direction) {
      case LEFT: {
        head = push_head(head, head->x - 2, head->y);
        break;
      }

      case RIGHT: {
        head = push_head(head, head->x + 2, head->y);
        break;
      }

      case UP: {
        head = push_head(head, head->x, head->y - 1);
        break;
      }
      case DOWN: {
        head = push_head(head, head->x, head->y + 1);
        break;
      }
      case NONE_DIR: {
        // Do not move or do anything else
        return;
      }
      }
    }
    case FOOD_TYPE_COUNT: {
      break;
    }
    }
  }
  switch (check_colliding(head)) {
  case COLLIDE_WITH_WALL: {
    _collide_with_wall();
    break;
  }
  case COLLIDE_WITH_SELF: {
    _collide_with_self();
    break;
  }
  case NOT_COLLIDING: {
    break;
  }
  }
}

static void _collide_with_wall() { gameRunning = 0; }
static void _collide_with_self() { gameRunning = 0; }
