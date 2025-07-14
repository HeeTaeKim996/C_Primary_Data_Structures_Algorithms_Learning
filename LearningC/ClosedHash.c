#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "ClosedHash.h"

static int Hash(int key, int size)
{
	return key >= 0 ? key % size : (key % size + size) % size;
}

static int Rehash(int key, int size)
{
	return ++key >= 0 ? key % size : (key % size + size) % size;
}

static void SetBucket(ClosedHash_Bucket* n, const Member* x, ClosedHash_Status stat)
{
	n->data = *x;
	n->stat = stat;
}

int ClosedHash_Initialize(ClosedHash* h, int size)
{
	if ((h->table = calloc(size, sizeof(ClosedHash_Bucket))) == NULL)
	{
		h->size = 0;
		return 0; // 실패
	}
	h->size = size;
	for (int i = 0; i < size; i++)
	{
		h->table[i].stat = ClosedHash_Empty;
	}
	return 1;
}

ClosedHash_Bucket* ClosedHash_Search(const ClosedHash* h, const Member* x)
{
	int key = Hash(x->no, h->size);
	ClosedHash_Bucket* p = &h->table[key];

	for (int i = 0; p->stat != ClosedHash_Empty && i < h->size; i++)
	{
		if (p->stat == ClosedHash_Occupied && p->data.no == x->no)
		{
			return p;
		}

		key = Rehash(key, h->size);
		p = &h->table[key];
	}

	return NULL;
}

int ClosedHash_Add(ClosedHash* h, const Member* x)
{
	if (ClosedHash_Search(h, x))
	{
		return 1; // 이미 등록
	}

	int key = Hash(x->no, h->size);
	ClosedHash_Bucket* p = &h->table[key];
	for (int i = 0; i < h->size; i++)
	{
		if (p->stat == ClosedHash_Empty || p->stat == ClosedHash_Deleted)
		{
			SetBucket(p, x, ClosedHash_Occupied);
			return 0; // 성공
		}

		key = Rehash(key, h->size);
		p = &h->table[key];
	}

	return 2; // 이미 가득참. 실패
}

int ClosedHash_Remove(ClosedHash* h, const Member* x)
{
	ClosedHash_Bucket* p = ClosedHash_Search(h, x);
	if (p == NULL)
	{
		return 1; // 없음
	}
	p->stat = ClosedHash_Deleted;
	return 0; // 성공
}

void ClosedHash_Dump(const ClosedHash* h)
{
	for (int i = 0; i < h->size; i++)
	{
		printf("%02d : ", i);
		switch (h->table[i].stat)
		{
		case ClosedHash_Occupied:
			printf("%02d (%s)\n", h->table[i].data.no, h->table[i].data.name);
			break;
		case ClosedHash_Empty:
			printf("--비어있음--\n");
			break;
		case ClosedHash_Deleted:
			printf("--삭제됨--\n");
			break;
		}
	}
}

void ClosedHash_Clear(ClosedHash* h)
{
	for (int i = 0; i < h->size; i++)
	{
		h->table[i].stat = ClosedHash_Empty;
	}
}

void ClosedHash_Terminate(ClosedHash* h)
{
	ClosedHash_Clear(h);
	free(h->table);
	h->size = 0;
}
