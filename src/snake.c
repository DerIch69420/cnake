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
  head->previous = NULL;

  return head;
}

SnakeNode *push_head(SnakeNode *head, int x, int y) {
  if (!head) {
    return NULL;
  }

  SnakeNode *new_head = (SnakeNode *)malloc(sizeof(SnakeNode));
  if (!new_head) {
    return NULL;
  }

  new_head->x = x;
  new_head->y = y;
  new_head->next = head;
  new_head->previous = NULL;

  head->previous = new_head;

  return new_head;
}

SnakeNode *add_segment(SnakeNode *tail, int x, int y) {
  if (!tail) {
    return NULL;
  }

  SnakeNode *newNode = (SnakeNode *)malloc(sizeof(SnakeNode));
  if (!newNode) {
    return NULL;
  }
  newNode->x = x;
  newNode->y = y;
  newNode->next = NULL;
  newNode->previous = tail;

  tail->next = newNode;

  return newNode;
}

SnakeNode *get_next(SnakeNode *tail) { return tail->next; }

SnakeNode *free_tail(SnakeNode *tail) {
  if (!tail) {
    return NULL;
  }

  SnakeNode *new_tail = tail->previous;
  if (!new_tail) {
    free(tail);
    return NULL;
  }
  new_tail->next = NULL;

  free(tail);

  return new_tail;
}

void free_snake(SnakeNode *head) {
  while (head) {
    SnakeNode *tmp = head;
    head = head->next;
    free(tmp);
  }
}
