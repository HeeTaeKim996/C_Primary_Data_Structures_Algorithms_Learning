#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "ChainHash.h"

static int Hash(int key, int size)
{
	return key >= 0 ? key % size : (key % size + size) % size;
	/*
	  - 뒤의 값을 -key % size; 로 처리해도 h->table[hashKey]가 균등 분배되어 문제 없지 않나 싶지만, 
	    현재 코드에는 없지만 Hash간 거리 계산에 문제가 된다. 예를 들어, 주석대로 할시 -1 과 1 은 같은 table에 할당된다.
		반면 위 코드대로 하면, -1 은 12 에 할당되어, -1 과 1의 해시 거리? 를 계산하면 11 또는 2 로 계산될 수 있음
	*/
}

static void SetNode(ChainHashNode* n, const Member* x, const ChainHashNode* next)
{
	n->data = *x;
	n->next = next;
}

int ChainHash_Initialize(ChainHash* h, int size)
{
	if ((h->table = calloc(size, sizeof(ChainHashNode*))) == NULL)
	{
		h->size = 0;
		return 0;
	}
	h->size = size;
	for (int i = 0; i < size; i++)
	{
		h->table[i] = NULL;
	}
	return 1;
}

ChainHashNode* ChainHash_Search(const ChainHash* h, const Member* x)
{
	int key = Hash(x->no, h->size);
	ChainHashNode* p = h->table[key];

	while (p != NULL)
	{
		if (p->data.no == x->no)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

int ChainHash_Add(ChainHash* h, const Member* x)
{
	int key = Hash(x->no, h->size);
	ChainHashNode* p = h->table[key];
	ChainHashNode* temp;

	while (p != NULL)
	{
		if (p->data.no == x->no)
		{
			return 1; // 중복 실패
		}
		p = p->next;
	}

	if ((temp = calloc(1, sizeof(ChainHashNode))) == NULL)
	{
		return 2; // 추가 실패
	}

	SetNode(temp, x, h->table[key]);
	h->table[key] = temp;
	return 0;
}

int ChainHash_Remove(ChainHash* h, const Member* x)
{
	int key = Hash(x->no, h->size);
	ChainHashNode* p = h->table[key];
	ChainHashNode** pp = &h->table[key];

	while (p != NULL)
	{
		if (p->data.no == x->no)
		{
			*pp = p->next;
			free(p);
			return 0; // 성공
		}
		pp = &p->next;
		p = p->next;
	}

	return 1; // 실패
}

void ChainHash_Dump(const ChainHash* h)
{
	for (int i = 0; i < h->size; i++)
	{
		printf("(%02d) :  ", i);
		ChainHashNode* p = h->table[i];
		while (p != NULL)
		{
			printf("-> %d (%s)  ", p->data.no, p->data.name);
			p = p->next;
		}
		putchar('\n');
	}
}

void ChainHash_Clear(ChainHash* h)
{
	for (int i = 0; i < h->size; i++)
	{
		ChainHashNode* p = h->table[i];
		while (p != NULL)
		{
			ChainHashNode* next = p->next;
			free(p);
			p = next;
		}
		h->table[i] = NULL;
	}
}

void ChainHash_Terminate(ChainHash* h)
{
	ChainHash_Clear(h);
	free(h->table);
	h->size = 0;
}
