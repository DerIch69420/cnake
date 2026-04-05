/*
 * src/food.c
 */

#include <stdlib.h>

#include "../game_settings.h"
#include "food.h"

static const int food_weights[FOOD_TYPE_COUNT] = {
    // Store probability of food types
    [FOOD_USELESS] = 10,
    [FOOD_NORMAL] = 60,
    [FOOD_DOUBLE] = 30};

static FoodType random_food_type(void) {
  int total = 0;

  for (int i = 0; i < FOOD_TYPE_COUNT; i++) {
    total += food_weights[i];
  }
  int r = rand() % total;

  int sum = 0;

  for (int i = 0; i < FOOD_TYPE_COUNT; i++) {
    sum += food_weights[i];
    if (r < sum) {
      return (FoodType)i;
    }
  }

  return FOOD_NORMAL;
}

Food *generate_food(int x_min, int x_max, int y_min, int y_max) {
  Food *new_food = (Food *)malloc(sizeof(Food));

  if (!new_food) {
    return NULL;
  }

  new_food->x = rand() % (x_max - x_min + 1) + x_min;
  new_food->y = rand() % (y_max - y_min + 1) + y_min;

  new_food->food_type = random_food_type();

  return new_food;
}

bool check_food(SnakeNode *head, Food **food) {
  if (((*food)->x == head->x) && ((*food)->y == head->y)) {
    Food *new_food = generate_food(X_MIN, X_MAX, Y_MIN, Y_MAX);

    if (new_food) {
      free(*food);
      *food = new_food;
    }

    return true;
  } else {
    return false;
  }
}
