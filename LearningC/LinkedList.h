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
	 �� __node : ����ü ���� ��� �뵵  vs Node : �ܺ� ��� �뵵
		- struct __node* next; �ڸ��� __node�� �ƴ� Node�� ����ϸ� ������ ����. ���� ����ü ������ ������� �ʾұ� ����.
		- �̷� ��, ���� ���뵵�� __node�� struct ���� ���� �����ϰ�, �ʵ� ����� ����
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
	 �� ���� ���� : �迭 ��� vs LinkedList(�����)  �� ���� 2���� �����ؼ�.. �Ѹ� ���ϴ� ���� ���� ����
	  - �迭 ��� : C++�� vector, ordered .. , C#�� list ��, Sort�� ����ϱ� ���� ĳ��ģȭ�� ����, �ε����� ����� ����� Ž���� �ʿ���
				   ����ü�� �ַ� ���
		�� Stack, Queue�� �迭 ����̶� ��. Deque, Enque���� ������ �� ȿ���� ���Ƽ��� ��..

	  - ��� ��� : C++�� set, map ��, ĳ��ģȭ��?�� Sort�� ������� �ʰų�(map�� ������ ������, ĳ��ģȭ������ ����
				   �����İ� ������? RedBlackTree ���), Sort��ü�� �ʿ� ����, ����ü. �ε����� Ž���� ���� �ʴ� ����ü�� ����

	  �� ���� Ʈ��, �ؽ� �� �߰� ���� ����

	*/

#ifdef __cplusplus
}

#endif // __cplusplus


#endif // __LinedList
