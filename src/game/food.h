/*
 * src/food.h
 */

#pragma once

#include <stdbool.h>

#include "snake.h"

typedef enum {
  NO_FOOD,
  NORMAL,
} FoodType;

typedef struct {
  int x;
  int y;
  FoodType food_type;
} Food;

Food *generate_food(int x_min, int x_max, int y_min, int y_max);

bool check_food(SnakeNode *head, Food **food);
