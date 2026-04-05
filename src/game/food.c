/*
 * src/food.c
 */

#include <stdlib.h>

#include "../game_settings.h"
#include "food.h"

Food *generate_food(int x_min, int x_max, int y_min, int y_max) {
  Food *new_food = (Food *)malloc(sizeof(Food));

  if (!new_food) {
    return NULL;
  }

  new_food->x = rand() % (x_max - x_min + 1) + x_min;
  new_food->y = rand() % (y_max - y_min + 1) + y_min;

  return new_food;
}

bool check_food(SnakeNode *head, Food **food) {
  if (((*food)->x == head->x) && ((*food)->y == head->y)) {
    *food = generate_food(X_MIN, X_MAX, Y_MIN, Y_MAX);
    return true;
  } else {
    return false;
  }
}
