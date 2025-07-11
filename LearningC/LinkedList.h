#ifndef ___LinkedList
#define ___LinedList
#include "Member.h"

typedef struct __node
{
	Member data;
	struct __node* next;
} Node;

typedef struct
{
	Node* head;
	Node* crnt;
} List;

inline void LinkedList_Initialize(List* list);

inline Node* LinkedList_Search(List* list, const Member* x, int compare(const Member* x, const Member* y));

inline void LinkedList_InsertFront(List* list, const Member* x);

inline void LinkedList_InsertRear(List* list, const Member* x);

inline void LinkedList_RemoveFront(List* list);

inline void LinkedList_RemoveRear(List* list);

inline void LinkedList_RemoveCurrent(List* list);

inline void LinkedList_Clear(List* list);

inline void LinkedList_PrintCurrent(const List* list);

inline void LinkedList_PrintLnCurrent(const List* list);

inline void LinkedList_Print(const List* list);

inline void LinkedList_Terminate(List* list);

#endif ___LinkedList