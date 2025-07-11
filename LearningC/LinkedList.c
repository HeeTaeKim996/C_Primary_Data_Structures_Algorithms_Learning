#include <stdio.h>
#include <stdlib.h>

#include "Member.h"
#include "LinkedList.h"

static Node* AllocNode()
{
	return calloc(1, sizeof(Node));
}

static void SetNode(Node* n, const Member* x, const Node* next)
{
	n->data = *x;
	n->next = next;
}

inline void LinkedList_Initialize(List* list)
{
	list->head = NULL;
	list->crnt = NULL;
}

inline Node* LinkedList_Search(List* list, const Member* x, int compare(const Member* x, const Member* y))
{
	Node* ptr = list->head;
	while (ptr != NULL)
	{
		if (compare(&ptr->data, x) == 0)
		{
			list->crnt = ptr;
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

inline void LinkedList_InsertFront(List* list, const Member* x)
{
	Node* ptr = list->head;
	list->head = list->crnt = AllocNode();
	SetNode(list->head, x, ptr);
}

inline void LinkedList_InsertRear(List* list, const Member* x)
{
	if (list->head == NULL)
	{
		LinkedList_InsertFront(list, x);
	}
	else
	{
		Node* ptr = list->head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = list->crnt = AllocNode();
		SetNode(ptr->next, x, NULL);
	}
}

inline void LinkedList_RemoveFront(List* list)
{
	if (list->head != NULL)
	{
		Node* ptr = list->head->next;
		free(list->head);
		list->head = list->crnt = ptr;
	}
}

inline void LinkedList_RemoveRear(List* list)
{
	
}

inline void LinkedList_RemoveCurrent(List* list)
{
}

inline void LinkedList_Clear(List* list)
{
}

inline void LinkedList_PrintCurrent(const List* list)
{
}

inline void LinkedList_PrintLnCurrent(const List* list)
{
}

inline void LinkedList_Print(const List* list)
{
}

inline void LinkedList_Terminate(List* list)
{
}
