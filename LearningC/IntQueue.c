#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

int IntQueue_Initialize(IntQueue* q, int max)
{
	q->num = q->front = q->rear = 0;
	if ((q->que = calloc(max, sizeof(int))) == NULL)
	{
		return -1;
	}
	q->max = max;
	return 0;
}

int IntQueue_Enque(IntQueue* q, int x)
{
	if (q->num >= q->max)
	{
		return -1;
	}

	q->num++;
	q->que[q->rear++] = x;
	if (q->rear == q->max)
	{
		q->rear = 0;
	}

	return 0;
}

int IntQueue_Deque(IntQueue* q, int* x)
{
	if (q->num <= 0)
	{
		return -1;
	}
	q->num--;
	*x = q->que[q->front++];
	if (q->front == q->max)
	{
		q->front = 0;
	}
	return 0;
}

int IntQueue_Peek(const IntQueue* q, int* x)
{
	if (q->num <= 0)
	{
		return -1;
	}

	*x = q->que[q->front];
	return 0;
}

void IntQueue_Clear(IntQueue* q)
{
	q->num = q->front = q->rear = 0;
}

int IntQueue_Capacity(const IntQueue* q)
{
	return q->max;
}

int IntQueue_Size(const IntQueue* q)
{
	return q->num;
}

int IntQueue_IsEmpty(const IntQueue* q)
{
	return q->num <= 0;
}

int IntQueue_IsFull(const IntQueue* q)
{
	return q->num >= q->max;
}

int IntQueue_Search(const IntQueue* q, int x)
{
	for (int i = 0; i < q->num; i++)
	{
		int idx;
		if (q->que[idx = (q->front + i) % q->max] == x)
		{
			return idx;
		}
	}
	return -1;
}

void IntQueue_Print(const IntQueue* q)
{
	for (int i = 0; i < q->num; i++)
	{
		printf("%d\t", q->que[(q->front + i) % q->max]);
	}
	putchar('\n');
}

void IntQueue_Terminate(IntQueue* q)
{
	if (q->que != NULL)
	{
		free(q->que);
		q->que = NULL;
	}
	q->max = q->num = q->front = q->rear = 0;
}
