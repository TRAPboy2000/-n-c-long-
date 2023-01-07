#include "CircularQueue.h"

Queue *queue_init(uint8_t l)
{
	Queue *self = (Queue*)malloc(sizeof(Queue));
	self->s = l;
	self->front = -1;
	self->rear = -1;
	self->ptr = (product*)malloc(sizeof(product)*self->s);
	return self;
}

bool IsEmpty(Queue *self)
{
	return(self->rear == -1 && self->front == -1);
}


bool IsFull(Queue *self)
{
	return(self->rear + 1) % self->s == self->front ? true : false;
}



void Enqueue(Queue *self, product x)
{
	if(IsFull(self))
	{
			return;
	}
	if (IsEmpty(self))	
	{ 
		self->front = self->rear = 0; 
	}
	else
	{
		self->rear = (self->rear+1)%self->s;
	}
	self->ptr[self->rear] = x;
}

void Dequeue(Queue *self)
{
	if(IsEmpty(self))
	{
		return;
	}
	else if(self->front == self->rear) 
	{
		self->rear = self->front = -1;
	}
	else
	{
		self->front = (self->front+1)%self->s;
	}
}

product Front(Queue *self)
{
  product junk;
	if(self->front == -1)
	{
    return; 
	}
	return self->ptr[self->front];
}
