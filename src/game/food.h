/*
 * src/food.h
 */

#pragma once

#include <stdbool.h>

#include "snake.h"

typedef enum {
  // Different types of food
  FOOD_USELESS,
  FOOD_NORMAL,
  FOOD_DOUBLE,

  // Count of different food types
  FOOD_TYPE_COUNT,
} FoodType;

typedef struct {
  int x;
  int y;
  FoodType food_type;
} Food;

Food *generate_food(int x_min, int x_max, int y_min, int y_max);

bool check_food(SnakeNode *head, Food **food);
