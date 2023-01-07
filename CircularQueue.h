#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include<stdlib.h>
#include<Arduino.h>
typedef struct
{
  char n;
  long timePass;
}product;

typedef struct
{
  uint8_t s;
  int8_t front, rear;
  product *ptr;
}Queue;


Queue *queue_init(uint8_t l);
bool IsEmpty(Queue *self);
bool IsFull(Queue *self);
void Enqueue(Queue *self, product x);
void Dequeue(Queue *self);
product Front(Queue *self);
#endif
