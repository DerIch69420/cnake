/*
 * src/snake.h
 */

typedef struct SnakeNode {
  int x;
  int y;
  struct SnakeNode *next;     // Next node of the snake
  struct SnakeNode *previous; // Previous node of the snake
} SnakeNode;

SnakeNode *create_head(int x, int y);
SnakeNode *push_head(SnakeNode *head, int x, int y);
SnakeNode *add_segment(SnakeNode *tail, int x, int y);
SnakeNode *get_next(SnakeNode *tail);
SnakeNode *free_tail(SnakeNode *tail);
void free_snake(SnakeNode *head);
