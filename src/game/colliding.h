/*
 * src/game/colliding.h
 */

#pragma once

#include <stdbool.h>

#include "../snake.h"

typedef enum {
  NOT_COLLIDING,
  COLLIDE_WITH_WALL,
  COLLIDE_WITH_SELF,
} Colliding;

Colliding check_colliding(SnakeNode *head);
