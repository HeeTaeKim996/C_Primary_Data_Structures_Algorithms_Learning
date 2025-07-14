#ifndef ___CircDbLinkedList
#define ___CircDbLinkedList

#ifdef __cplusplus
extern "C"
{
#endif

#include "Member.h"

	typedef struct __CircDbLinkedList_Node
	{
		Member data;
		struct __CircDbLinkedList_Node* prev;
		struct __CircDbLinkedList_Node* next;
	} CircDbLinkedList_Node;

	typedef struct
	{
		CircDbLinkedList_Node* head;
		CircDbLinkedList_Node* crnt;
	} CircDbLinkedList;

	void CircDbLinkedList_Initialize(CircDbLinkedList* list);

	void CircDbLinkedList_PrintCurrent(const CircDbLinkedList* list);

	void CircDbLinkedList_PrintLnCurrent(const CircDbLinkedList* list);

	CircDbLinkedList_Node* CircDbLinkedList_Search(CircDbLinkedList* list, const Member* x,
		int Compare(const Member* x, const Member* y));

	void CircDbLinkedList_Print(const CircDbLinkedList* list);

	void CircDbLinkedList_PrintReverse(const CircDbLinkedList* list);

	int CircDbLinkedList_Next(CircDbLinkedList* list);

	int CircDbLinkedList_Prev(CircDbLinkedList* list);

	void CircDbLinkedList_InsertAfter(CircDbLinkedList* list, CircDbLinkedList_Node* p, const Member* x);

	void CircDbLinkedList_InsertFront(CircDbLinkedList* list, const Member* x);

	void CircDbLinkedList_InsertRear(CircDbLinkedList* list, const Member* x);

	void CircDbLinkedList_Remove(CircDbLinkedList* list, CircDbLinkedList_Node* p);

	void CircDbLinkedList_RemoveFront(CircDbLinkedList* list);

	void CircDbLinkedList_RemoveRear(CircDbLinkedList* list);

	void CircDbLinkedList_RemoveCurrent(CircDbLinkedList* list);

	void CircDbLinkedList_Clear(CircDbLinkedList* list);

	void CircDbLinkedList_Terminate(CircDbLinkedList* list);



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___CircDbLinkedList








