/*
 * src/game/colliding.c
 */

#include "colliding.h"
#include "../game_settings.h"

Colliding check_colliding(SnakeNode *head) {
  // Colliding with wall
  if ((head->x < X_MIN) || (head->x + 1 > X_MAX_TERMINAL) ||
      (head->y < Y_MIN) || (head->y > Y_MAX)) {
    return COLLIDE_WITH_WALL;
  }

  // Colliding with itself
  SnakeNode *bodyPart = head;
  while ((bodyPart = get_next(bodyPart))) {
    if (((head->x == bodyPart->x) && (head->y == bodyPart->y)) ||
        ((head->x == bodyPart->x) && (head->y == bodyPart->y))) {
      return COLLIDE_WITH_SELF;
    }
  }

  // Not colliding with anything
  return NOT_COLLIDING;
}
