#ifndef SEMAPHORES_LIBRARY_H
#define SEMAPHORES_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>


#define N 5
#define SIZE 5

typedef enum {false, true} bool;

struct FIFO
{
	int size;
	int buffer[SIZE];
	int head, tail;

};

typedef struct FIFO FIFO;

int push(FIFO *que, int value)
{
	if(que->size >= SIZE)
		return -1;
	que->buffer[que->head] = value;
	que->head= ++(que->head) % SIZE;
	++(que->size);

	return 0;
}

int pop(FIFO *que)
{
	int retVal;

	if(que->size == 0)
		return -1;

	--(que->size);
	retVal = que->buffer[que->tail];
	que->tail= ++(que->tail) % SIZE;

	return retVal;
}

int getQueueSize(FIFO *que)
{
	return que->size;
}

void printQue(FIFO *que, int queIndex)
{
	int i=0, index = que->tail;
	printf("Stan klejki %d: ", queIndex);

	while(i++ < que->size)
	{
		printf("%d ", que->buffer[index]);
		index = (index+1) % SIZE;
	}
	printf("\n");
}

#endif