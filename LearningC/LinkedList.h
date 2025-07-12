#ifndef ___LinkedList
#define ___LinkedList

#ifdef __cplusplus
extern "C" {
#endif 


#include "Member.h"

	typedef struct __node
	{
		Member data;
		struct __node* next;
	} LinkedList_Node;
	/*
	 ○ __node : 구조체 내부 사용 용도  vs Node : 외부 사용 용도
		- struct __node* next; 자리에 __node가 아닌 Node를 사용하면 컴파일 오류. 아직 구조체 선언이 종료되지 않았기 때문.
		- 이럴 때, 내부 사용용도의 __node를 struct 옆에 먼저 정의하고, 필드 멤버로 정의
	*/

	typedef struct
	{
		LinkedList_Node* head;
		LinkedList_Node* crnt;
	} LinkedList;

	void LinkedList_Initialize(LinkedList* list);

	LinkedList_Node* LinkedList_Search(LinkedList* list, const Member* x, int compare(const Member* x, const Member* y));

	void LinkedList_InsertFront(LinkedList* list, const Member* x);

	void LinkedList_InsertRear(LinkedList* list, const Member* x);

	void LinkedList_RemoveFront(LinkedList* list);

	void LinkedList_RemoveRear(LinkedList* list);

	void LinkedList_RemoveCurrent(LinkedList* list);

	void LinkedList_Clear(LinkedList* list);

	void LinkedList_PrintCurrent(const LinkedList* list);

	void LinkedList_PrintLnCurrent(const LinkedList* list);

	void LinkedList_Print(const LinkedList* list);

	void LinkedList_Terminate(LinkedList* list);





	/*
	 ○ 공부 정리 : 배열 기반 vs LinkedList(노드기반)  ※ 지금 2개만 공부해서.. 둘만 비교하는 공부 내용 정리
	  - 배열 기반 : C++의 vector, ordered .. , C#의 list 등, Sort를 사용하기 위한 캐시친화적 구조, 인덱스를 사용한 빈번한 탐색이 필요한
				   구조체에 주로 사용
		※ Stack, Queue도 배열 기반이라 함. Deque, Enque에서 접근할 때 효율이 좋아서라 함..

	  - 노드 기반 : C++의 set, map 등, 캐시친화적?인 Sort를 사용하지 않거나(map은 정렬을 하지만, 캐시친화적이지 않은
				   힙정렬과 유사한? RedBlackTree 사용), Sort자체가 필요 없는, 구조체. 인덱스로 탐색을 하지 않는 구조체에 적합

	  ※ 추후 트리, 해시 등 추가 공부 예정

	*/

#ifdef __cplusplus
}

#endif // __cplusplus


#endif // __LinedList
