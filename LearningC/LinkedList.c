#include <stdio.h>
#include <stdlib.h>

#include "Member.h"
#include "LinkedList.h"

static LinkedList_Node* AllocNode()
{
	return calloc(1, sizeof(LinkedList_Node));
}

static void SetNode(LinkedList_Node* n, const Member* x, const LinkedList_Node* next)
{
	n->data = *x;
	n->next = next;
}

void LinkedList_Initialize(LinkedList* list)
{
	list->head = NULL;
	list->crnt = NULL;
}

LinkedList_Node* LinkedList_Search(LinkedList* list, const Member* x, int compare(const Member* x, const Member* y))
{
	LinkedList_Node* ptr = list->head;
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

void LinkedList_InsertFront(LinkedList* list, const Member* x)
{
	LinkedList_Node* ptr = list->head;
	list->head = list->crnt = AllocNode();
	SetNode(list->head, x, ptr);
}

void LinkedList_InsertRear(LinkedList* list, const Member* x)
{
	if (list->head == NULL)
	{
		LinkedList_InsertFront(list, x);
	}
	else
	{
		LinkedList_Node* ptr = list->head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = list->crnt = AllocNode();
		SetNode(ptr->next, x, NULL);
	}
}

void LinkedList_RemoveFront(LinkedList* list)
{
	if (list->head != NULL)
	{
		LinkedList_Node* ptr = list->head->next;
		free(list->head);
		list->head = list->crnt = ptr;
	}
}

void LinkedList_RemoveRear(LinkedList* list)
{
	if (list->head != NULL)
	{
		if (list->head->next == NULL)
		{
			LinkedList_RemoveFront(list);
		}
		else
		{
			LinkedList_Node* ptr = list->head;
			LinkedList_Node* pre = NULL;
			while (ptr->next != NULL)
			{
				pre = ptr;
				ptr = ptr->next;
			}

			pre->next = NULL;
			free(ptr);
			list->crnt = pre;
		}
	}
}

void LinkedList_RemoveCurrent(LinkedList* list)
{
	if (list->head != NULL)
	{
		if (list->head == list->crnt)
		{
			LinkedList_RemoveFront(list);
		}
		else
		{
			LinkedList_Node* ptr = list->head;
			while (ptr->next != list->crnt)
			{
				ptr = ptr->next;
			}
			ptr->next = list->crnt->next;
			free(list->crnt);
			list->crnt = ptr;
		}
	}
}

void LinkedList_Clear(LinkedList* list)
{
	if (list->head != NULL)
	{
		LinkedList_Node* ptr = list->head;
		while (ptr->next != NULL)
		{
			LinkedList_Node* next = ptr->next;
			free(ptr);
			ptr = next;
		}
		free(ptr);
		list->head = NULL;
	}
	list->crnt = NULL;
}

void LinkedList_PrintCurrent(const LinkedList* list)
{
	if (list->crnt == NULL)
	{
		printf("선택한 노드가 없습니다");
	}
	else
	{
		Member_PrintMember(&list->crnt->data);
	}
}

void LinkedList_PrintLnCurrent(const LinkedList* list)
{
	if (list->crnt == NULL)
	{
		printf("선택한 노드가 없습니다\n");
	}
	else
	{
		Member_PrintLnMember(&list->crnt->data);
	}
}

void LinkedList_Print(const LinkedList* list)
{
	if (list->head != NULL)
	{
		puts("모두보기");
		LinkedList_Node* ptr = list->head;
		while (ptr != NULL)
		{
			Member_PrintLnMember(&ptr->data);
			ptr = ptr->next;
		}
	}
	else
	{
		printf("노드가 없습니다\n");
	}
}

void LinkedList_Terminate(LinkedList* list)
{
	LinkedList_Clear(list);
}
