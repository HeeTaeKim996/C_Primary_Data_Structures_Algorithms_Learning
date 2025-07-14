#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "ChainHash.h"

static int Hash(int key, int size)
{
	return key >= 0 ? key % size : (key % size + size) % size;
	/*
	  - ���� ���� -key % size; �� ó���ص� h->table[hashKey]�� �յ� �й�Ǿ� ���� ���� �ʳ� ������, 
	    ���� �ڵ忡�� ������ Hash�� �Ÿ� ��꿡 ������ �ȴ�. ���� ���, �ּ���� �ҽ� -1 �� 1 �� ���� table�� �Ҵ�ȴ�.
		�ݸ� �� �ڵ��� �ϸ�, -1 �� 12 �� �Ҵ�Ǿ�, -1 �� 1�� �ؽ� �Ÿ�? �� ����ϸ� 11 �Ǵ� 2 �� ���� �� ����
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
			return 1; // �ߺ� ����
		}
		p = p->next;
	}

	if ((temp = calloc(1, sizeof(ChainHashNode))) == NULL)
	{
		return 2; // �߰� ����
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
			return 0; // ����
		}
		pp = &p->next;
		p = p->next;
	}

	return 1; // ����
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
