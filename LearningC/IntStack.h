#pragma once

#ifndef ___IntStack
#define ___IntStack

typedef struct
{
	int max;
	int ptr;
	int* stk;
} IntStack;

int IntStack_Initialize(IntStack* s, int max);

int IntStack_Push(IntStack* s, int x);

int IntStack_Pop(IntStack* s, int* x);

int IntStack_Peek(const IntStack* s, int* x);

void IntStack_Clear(IntStack* s);

int IntStack_Capacity(const IntStack* s);

int IntStack_Size(const IntStack* s);

int IntStack_IsFull(const IntStack* s);

int IntStack_IsEmpty(const IntStack* s);

int IntStack_Search(const IntStack* s, int x);

void IntStack_Print(const IntStack* s);

void IntStack_Terminate(IntStack* s);
#endif


