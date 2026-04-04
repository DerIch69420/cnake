/*
 * src/food.h
 */

typedef struct {
  int x;
  int y;
} Food;

Food *generate_food(int x_min, int x_max, int y_min, int y_max);
