/*
 * src/food.c
 */

#include <stdlib.h>

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
