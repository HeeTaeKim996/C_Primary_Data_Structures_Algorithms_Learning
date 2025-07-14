#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "CircDbLinkedList.h"

static CircDbLinkedList_Node* AllocNode()
{
	return calloc(1, sizeof(CircDbLinkedList_Node));
}

static void SetNode(CircDbLinkedList_Node* n, const Member* x, const CircDbLinkedList_Node* prev, 
	const CircDbLinkedList_Node* next)
{
	n->data = *x;
	n->prev = prev;
	n->next = next;
}

static int IsEmpty(const CircDbLinkedList* list)
{
	return list->head->next == list->head;
}

void CircDbLinkedList_Initialize(CircDbLinkedList* list)
{
	CircDbLinkedList_Node* dummyNode = AllocNode();
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

void CircDbLinkedList_PrintCurrent(const CircDbLinkedList* list)
{
	if (IsEmpty(list))
	{
		printf("선택한 노드가 없습니다\n");
	}
	else
	{
		Member_PrintLnMember(&list->crnt->data);
	}
}

void CircDbLinkedList_PrintLnCurrent(const CircDbLinkedList* list)
{
	CircDbLinkedList_PrintCurrent(list);
	putchar('\n');
}

CircDbLinkedList_Node* CircDbLinkedList_Search(CircDbLinkedList* list, const Member* x, int Compare(const Member* x, const Member* y))
{
	CircDbLinkedList_Node* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (Compare(&ptr->data, x) == 0)
		{
			list->crnt = ptr;
			return ptr;
		}

		ptr = ptr->next;
	}

	return NULL;
}

void CircDbLinkedList_Print(const CircDbLinkedList* list)
{
	if (IsEmpty(list))
	{
		puts("노드가 없습니다");
	}
	else
	{
		CircDbLinkedList_Node* ptr = list->head->next;
		puts("모두보기");

		while (ptr != list->head)
		{
			Member_PrintLnMember(&ptr->data);
			ptr = ptr->next;
		}
	}
}

void CircDbLinkedList_PrintReverse(const CircDbLinkedList* list)
{
	if (IsEmpty(list))
	{
		puts("노드가 없습니다");
	}
	else
	{
		CircDbLinkedList_Node* ptr = list->head->prev;
		puts("모두보기");

		while (ptr != list->head)
		{
			Member_PrintLnMember(&ptr->data);
			ptr = ptr->prev;
		}
	}
}

int CircDbLinkedList_Next(CircDbLinkedList* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
	{
		return 0;
	}
	else
	{
		list->crnt = list->crnt->next;
		return 1;
	}
}

int CircDbLinkedList_Prev(CircDbLinkedList* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
	{
		return 0;
	}
	else
	{
		list->crnt = list->crnt->prev;
		return 1;
	}
}

void CircDbLinkedList_InsertAfter(CircDbLinkedList* list, CircDbLinkedList_Node* p, const Member* x)
{
	CircDbLinkedList_Node* ptr = AllocNode();
	SetNode(ptr, x, p, p->next);
	p->next = p->next->prev = ptr;
	list->crnt = ptr;
}

void CircDbLinkedList_InsertFront(CircDbLinkedList* list, const Member* x)
{
	CircDbLinkedList_InsertAfter(list, list->head, x);
}

void CircDbLinkedList_InsertRear(CircDbLinkedList* list, const Member* x)
{
	CircDbLinkedList_InsertAfter(list, list->head->prev, x);
}

void CircDbLinkedList_Remove(CircDbLinkedList* list, CircDbLinkedList_Node* p)
{
	p->prev->next = p->next;
	list->crnt = p->next->prev = p->prev;
	free(p);

	if (list->crnt == list->head)
	{
		list->crnt = list->head->next;
	}
}

void CircDbLinkedList_RemoveFront(CircDbLinkedList* list)
{
	if (!IsEmpty(list))
	{
		CircDbLinkedList_Remove(list, list->head->next);
	}
}

void CircDbLinkedList_RemoveRear(CircDbLinkedList* list)
{
	if (!IsEmpty(list))
	{
		CircDbLinkedList_Remove(list, list->head->prev);
	}
}

void CircDbLinkedList_RemoveCurrent(CircDbLinkedList* list)
{
	if (list->crnt != list->head)
	{
		CircDbLinkedList_Remove(list, list->crnt);
	}
}

void CircDbLinkedList_Clear(CircDbLinkedList* list)
{
	if (!IsEmpty(list))
	{
		CircDbLinkedList_Node* ptr = list->head->next;
		while (ptr != list->head)
		{
			CircDbLinkedList_Node* next = ptr->next;
			free(ptr);
			ptr = next;
		}

		list->head->next = list->head->prev = list->crnt = list->head;
	}
}

void CircDbLinkedList_Terminate(CircDbLinkedList* list)
{
	CircDbLinkedList_Clear(list);
	free(list->head);
}
