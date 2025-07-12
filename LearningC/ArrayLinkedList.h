#ifndef ___ArrayLinkedList
#define ___ArrayLinkedList

#ifdef __cplusplus
extern "C" {
#endif

#include "Member.h"

#define Null -1

	typedef int Index;

	typedef struct
	{
		Member data;
		Index next;
		Index dNext;
	} ArrayLinkedList_Node;

	typedef struct
	{
		ArrayLinkedList_Node* n;
		Index head;
		Index max;
		Index deleted;
		Index crnt;
	} ArrayLinkedList;

	void ArrayLinkedList_Initialize(ArrayLinkedList* list, int size);

	Index ArrayLinkedList_Search(ArrayLinkedList* list, const Member* x, int compare(const Member* x, const Member* y));

	void ArrayLinkedList_InsertFront(ArrayLinkedList* list, const Member* x);

	void ArrayLinkedList_InsertRear(ArrayLinkedList* list, const Member* x);

	void ArrayLinkedList_RemoveFront(ArrayLinkedList* list);

	void ArrayLinkedList_RemoveRear(ArrayLinkedList* list);

	void ArrayLinkedList_RemoveCurrent(ArrayLinkedList* list);

	void ArrayLinkedList_Clear(ArrayLinkedList* list);

	void ArrayLinkedList_PrintCurrent(const ArrayLinkedList* list);

	void ArrayLinkedList_PrintLnCurrent(const ArrayLinkedList* list);

	void ArrayLinkedList_Print(const ArrayLinkedList* list);

	void ArrayLinkedList_Terminate(ArrayLinkedList* list);

#ifdef __cplusplus
}

#endif // __cplusplus

#endif // ArrayLinkedList

