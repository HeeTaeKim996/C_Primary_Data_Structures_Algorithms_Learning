#ifndef ___IntQueue
#define ___IntQueue

typedef struct
{
	int max;
	int num;
	int front;
	int rear;
	int* que;
} IntQueue;

int IntQueue_Initialize(IntQueue* q, int max);

int IntQueue_Enque(IntQueue* q, int x);

int IntQueue_Deque(IntQueue* q, int* x);

int IntQueue_Peek(const IntQueue* q, int* x);

void IntQueue_Clear(IntQueue* q);

int IntQueue_Capacity(const IntQueue* q);

int IntQueue_Size(const IntQueue* q);

int IntQueue_IsEmpty(const IntQueue* q);

int IntQueue_IsFull(const IntQueue* q);

int IntQueue_Search(const IntQueue* q, int x);

void IntQueue_Print(const IntQueue* q);

void IntQueue_Terminate(IntQueue* q);
#endif 