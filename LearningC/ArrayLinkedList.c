#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "ArrayLinkedList.h"

static Index GetIndex(ArrayLinkedList* list)
{
	if (list->deleted == Null)
	{
		return ++(list->max); // capacity 확인하지 않으니, 메모리 오염 가능성 있음. 교육용이니 안한듯
	}
	else
	{
		Index rec = list->deleted;
		list->deleted = list->n[rec].dNext;
		return rec;
	}
}

static void DeleteIndex(ArrayLinkedList* list, Index idx)
{
	if (list->deleted == Null)
	{
		list->deleted = idx;
		list->n[idx].dNext = Null;
	}
	else
	{
		Index ptr = list->deleted;
		list->deleted = idx;
		list->n[idx].dNext = ptr;
	}
}

static void SetNode(ArrayLinkedList_Node* node, const Member* x, Index next)
{
	node->data = *x;
	node->next = next;
}

void ArrayLinkedList_Initialize(ArrayLinkedList* list, int size)
{
	list->n = calloc(size, sizeof(ArrayLinkedList_Node));
	list->head = Null;
	list->crnt = Null;
	list->max = Null;
	list->deleted = Null;
}

Index ArrayLinkedList_Search(ArrayLinkedList* list, const Member* x, int compare(const Member* x, const Member* y))
{
	Index ptr = list->head;
	while (ptr != Null)
	{
		if (compare(&list->n[ptr].data, x) == 0)
		{
			list->crnt = ptr;
			return ptr;
		}
		ptr = list->n[ptr].next;
	}
	return Null;
}

void ArrayLinkedList_InsertFront(ArrayLinkedList* list, const Member* x)
{
	Index ptr = list->head;
	list->head = list->crnt = GetIndex(list);
	SetNode(&list->n[list->head], x, ptr);
}

void ArrayLinkedList_InsertRear(ArrayLinkedList* list, const Member* x)
{
	if (list->head != Null)
	{
		Index ptr = list->head;
		while (list->n[ptr].next != Null)
		{
			ptr = list->n[ptr].next;
		}
		list->n[ptr].next = list->crnt = GetIndex(list);
		SetNode(&list->n[list->n[ptr].next], x, Null);
	}
	else
	{
		list->head = GetIndex(list);
		SetNode(&list->n[list->head], x, Null);
	}
}

void ArrayLinkedList_RemoveFront(ArrayLinkedList* list)
{
	if (list->head != Null)
	{
		Index ptr = list->n[list->head].next;
		DeleteIndex(list, list->head);
		list->head = list->crnt = ptr;
	}
}

void ArrayLinkedList_RemoveRear(ArrayLinkedList* list)
{
	if (list->head != Null)
	{

		if (list->n[list->head].next == Null)
		{
			DeleteIndex(list, list->head);
			list->head = list->crnt = Null;
		}
		else
		{
			Index ptr = list->head;
			Index pre;
			while (list->n[ptr].next != Null)
			{
				pre = ptr;
				ptr = list->n[ptr].next;
			}

			list->n[pre].next = Null;
			DeleteIndex(list, ptr);
			list->crnt = pre;
		}
	}
}

void ArrayLinkedList_RemoveCurrent(ArrayLinkedList* list)
{
	if (list->head != Null)
	{
		if (list->head == list->crnt)
		{
			Index ptr = list->n[list->head].next;
			DeleteIndex(list, list->head);
			list->head = list->crnt = ptr;
		}
		else
		{
			Index ptr = list->head;
			while (list->n[ptr].next != list->crnt)
			{
				ptr = list->n[ptr].next;
			}

			list->n[ptr].next = list->n[list->crnt].next;
			DeleteIndex(list, list->crnt);
			list->crnt = ptr;
		}
	}
}

void ArrayLinkedList_Clear(ArrayLinkedList* list)
{
	while (list->head != Null)
	{
		ArrayLinkedList_RemoveFront(list);
	}
	// ※ 노드들의 dNext 갱신을 위해 반복문 필요
}

void ArrayLinkedList_PrintCurrent(const ArrayLinkedList* list)
{
	if (list->crnt == Null)
	{
		printf("선택된 노드가 없습니다");
	}
	else
	{
		Member_PrintMember(&(list->n[list->crnt].data));		
	}
}

void ArrayLinkedList_PrintLnCurrent(const ArrayLinkedList* list)
{
	ArrayLinkedList_PrintCurrent(list);
	putchar('\n');
}

void ArrayLinkedList_Print(const ArrayLinkedList* list)
{
	if (list->head != Null)
	{
		puts("모두 보기\n");
		Index ptr = list->head;
		while (ptr != Null)
		{
			Member_PrintLnMember(&list->n[ptr].data);
			ptr = list->n[ptr].next;
		}
	}
	else
	{
		puts("노드가 없습니다");
	}
}

void ArrayLinkedList_Terminate(ArrayLinkedList* list)
{
	ArrayLinkedList_Clear(list);
	free(list->n);
}
