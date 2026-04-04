/*
 * src/snake.c
 */

#include <stdlib.h>

#include "snake.h"

SnakeNode *create_head(int x, int y) {
  SnakeNode *head = (SnakeNode *)malloc(sizeof(SnakeNode));
  if (!head) {
    return NULL;
  }

  head->x = x;
  head->y = y;
  head->next = NULL;
  head->next = NULL;

  return head;
}

void add_segment(SnakeNode *tail, int x, int y) {
  SnakeNode *newNode = (SnakeNode *)malloc(sizeof(SnakeNode));
  if (!newNode) {
    return;
  }
  newNode->x = x;
  newNode->y = y;
  newNode->next = NULL;
  newNode->previous = tail;

  tail->next = newNode;
}

SnakeNode *get_next(SnakeNode *tail) { return tail->next; }

void free_snake(SnakeNode *head) {
  while (head) {
    SnakeNode *tmp = head;
    head = head->next;
    free(tmp);
  }
}
