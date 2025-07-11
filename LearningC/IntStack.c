#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"

int IntStack_Initialize(IntStack* s, int max)
{
	s->ptr = 0;
	if ((s->stk = calloc(max, sizeof(int))) == NULL)
	{
		s->max = 0;
		return -1;
	}
	s->max = max;
	return 0;
}

int IntStack_Push(IntStack* s, int x)
{
	if (s->ptr >= s->max)
	{
		return -1;
	}
	s->stk[s->ptr++] = x;
	return 0;
}

int IntStack_Pop(IntStack* s, int* x)
{
	if (s->ptr <= 0)
	{
		return -1;
	}
	*x = s->stk[--s->ptr];
	return 0;
}


int IntStack_Peek(const IntStack* s, int* x)
{
	if (s->ptr <= 0)
	{
		return -1;
	}
	*x = s->stk[s->ptr - 1];
	return 0;
}

void IntStack_Clear(IntStack* s)
{
	s->ptr = 0;
}

int IntStack_Capacity(const IntStack* s)
{
	return s->max;
}

int IntStack_Size(const IntStack* s)
{
	return s->ptr;
}

int IntStack_IsFull(const IntStack* s)
{
	return s->ptr >= s->max;
}

int IntStack_IsEmpty(const IntStack* s)
{
	return s->ptr <= 0;
}

int IntStack_Search(const IntStack* s, int x)
{
	for (int i = s->ptr - 1; i >= 0; i--)
	{
		if (s->stk[i] == x)
		{
			return i;
		}
	}
	return -1;
}

void IntStack_Print(const IntStack* s)
{
	for (int i = 0; i < s->ptr; i++)
	{
		printf("%d\t", s->stk[i]);
	}
	putchar('\n');
}

void IntStack_Terminate(IntStack* s)
{
	if (s->stk != NULL)
	{
		free(s->stk);
		s->stk = NULL;
	}
	s->max = s->ptr = 0;
}
