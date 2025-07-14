#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sortings.h"
#include "time.h"
#include "StringMatch.h"
#include "Member.h"
#include "LinkedList.h"
#include "ArrayLinkedList.h"
#include "CircDbLinkedList.h"
#include "BinTree.h"

int int_cmp(const int* a, const int* b)
{
	if (*a > *b)
	{
		return 1;
	}
	else if (*a < *b)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
typedef struct
{
	char name[10];
	int height;
	int weight;
} Person;
int npcmp(const Person* x, const Person* y)
{
	return strcmp(x->name, y->name);
}
int hpcmp(const Person* x, const Person* y)
{
	if (x->height > y->height)
	{
		return 1;
	}
	else if (x->height < y->height)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int wpcmp(const Person* x, const Person* y)
{
	if (x->weight > y->weight)
	{
		return -1;
	}
	else if (x->weight < y->weight)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Print_Person(const Person persons[], int nx)
{
	for (int i = 0; i < nx; i++)
	{
		printf("%-10s %dcm %dkg \n", persons[i].name, persons[i].height, persons[i].weight);
	}
	putchar('\n');
}

typedef enum
{
	TERMINATE, INS_FRONT, INS_REAR, RMV_FRONT, RMV_REAR, PRINT_CRNT, RMV_CRNT, SRCH_NO, SRCH_NAME, PRINT_ALL, CLEAR
} LinkedList_Menu;
LinkedList_Menu LinkedList_SelectMenu(void)
{
	int ch;
	char* mstring[] =
	{
		"머리에 노드를 삽입", "꼬리에 노드를 삽입", "머리 노드를 삭제", "꼬리 노드를 삭제", "선택한 노드를 출력", "선택한 노드를 삭제",
		"번호로 검색", "이름으로 검색", "모든 노드를 출력", "모든 노드를 삭제"
	};
	do
	{
		for (int i = TERMINATE; i < CLEAR; i++)
		{
			printf("(%2d) %-18.18s ", i + 1, mstring[i]);
			if ((i % 3) == 2)
			{
				putchar('\n');
			}
		}
		printf("(0) 종료 : ");
		scanf("%d", &ch);
	} while (ch < TERMINATE || ch > CLEAR);
	return (LinkedList_Menu)ch;
}

typedef enum
{
	CircDbLinkedList_TERMINATE, CircDbLinkedList_INS_FRONT, CircDbLinkedList_INS_REAR, CircDbLinkedList_RMV_FRONT,
	CircDbLinkedList_RMV_REAR, CircDbLinkedList_PRINT_CRNT, CircDbLinkedList_RMV_CRNT, CircDbLinkedList_SRCH_NO,
	CircDbLinkedList_SRCH_NAME, CircDbLinkedList_PRINT_ALL, CircDbLinkedList_NEXT, CircDbLinkedList_PREV,
	CircDbLinkedList_CLEAR
} CircDbLinkedList_Menu;
CircDbLinkedList_Menu CircDbLinkedList_SelectMenu()
{
	int ch;
	char* mstring[] =
	{
		"머리에 노드를 삽입", "꼬리에 노드를 삽입", "모리 노드를 삭제", "꼬리 노드를 삭제", "선택한 노드를 출력",
		"선택한 노드를 삭제", "번호로 검색", "이름으로 검색", "모든 노드를 출력", "선택한 노드를 뒤쪽으로",
		"선택한 노드를 앞쪽으로", "모든 노드를 삭제"
	};
	
	do
	{
		for (int i = CircDbLinkedList_TERMINATE; i < CircDbLinkedList_CLEAR; i++)
		{
			printf("(%2d) %-22.22s  ", i + 1, mstring[i]);
			if (i % 3 == 2)
			{
				putchar('\n');
			}
		}
		printf("종료(0) : ");
		scanf("%d", &ch);
	} while (ch < CircDbLinkedList_TERMINATE || ch > CircDbLinkedList_CLEAR);
	return(CircDbLinkedList_Menu)ch;
}


typedef enum
{
	ArrayLinkedList_TERMINATE, ArrayLinkedList_INS_FRONT, ArrayLinkedList_INS_REAR, ArrayLinkedList_RMV_FRONT, ArrayLinkedList_RMV_REAR, 
	ArrayLinkedList_PRINT_CRNT, ArrayLinkedList_RMV_CRNT, ArrayLinkedList_SRCH_NO, ArrayLinkedList_SRCH_NAME, 
	ArrayLinkedList_PRINT_ALL, ArrayLinkedList_CLEAR
} ArrayLinkedList_Menu;

ArrayLinkedList_Menu ArrayLinkedList_SelectMenu()
{
	int ch;
	char* mstring[] =
	{
		"머리에 노드를 삽입", "꼬리에 노드를 삽입", "머리 노드를 삭제", "꼬리 노드를 삭제", "선택한 노드를 출력", "선택한 노드를 삭제", 
		"번호로 검색", "이름으로 검색", "모든 노드를 출력", "모든 노드를 삭제"
	};
	do
	{
		for (int i = ArrayLinkedList_TERMINATE; i < ArrayLinkedList_CLEAR; i++)
		{
			printf("(%2d) %-18.18s  ", i + 1, mstring[i]);
			if ((i % 3) == 2)
			{
				putchar('\n');
			}
		}
		printf("(0) 종료: ");
		scanf("%d", &ch);
	} while (ch < ArrayLinkedList_TERMINATE || ch > ArrayLinkedList_CLEAR);
	return (ArrayLinkedList_Menu)ch;
}


typedef enum
{
	BinTree_TERMINATE, BinTree_ADD, BinTree_REMOVE, BinTree_SEARCH, BinTree_PRINT
} BinTree_Menu;

BinTree_Menu BinTree_SelectMenu()
{
	int ch;
	do
	{
		printf("(1)삽입 (2)삭제 (3)검색 (4)출력 (0)종료 : ");
		scanf("%d", &ch);
	} while (ch < BinTree_TERMINATE || ch > BinTree_PRINT);

	return (BinTree_Menu)ch;
}

void main()
{

	if (0)
	{
		//int arr[] = { 9,6,5,7,3,1,4,2,8 };

		//int arr[] = { 1,2,3,4,5,6,7,9,8 };

		//int arr[] = { 9,8,7,6,5,4,3,2,1 };

		int arr[14];
		int count = 14;
		int index = 0;
		srand(time(NULL));
		while (1)
		{
		here:;

			int randValue = rand() % (count);

			for (int i = 0; i < index; i++)
			{
				if (arr[i] == randValue)
				{
					goto here;
				}
			}

			arr[index] = randValue;

			if (++index >= count)
			{
				break;
			}
			
		}


		

		//QuickSort_4(arr, 0, count - 1);

		//HeapSort(arr, count);
		
		CountingSort(arr, 13, 14);

		for (int i = 0; i < count; i++)
		{
			printf("%d\t", arr[i]);
		}
	}

	if (0)
	{
		int arr[] = { 9,6,5,7,3,1,4,2,8 };

		qsort(arr, 9, sizeof(int), (int(*)(const void*, const void*))int_cmp);

		for (int i = 0; i < 9; i++)
		{
			printf("%d\t", arr[i]);
		}

	}

	if (0)
	{
		Person persons[] = 
		{
			{"Harry", 12, 5},
			{"Bori", 9, 4},
			{"Heetae", 176, 70}
		};

		int nx = sizeof(persons) / sizeof(persons[0]);

		Print_Person(persons, nx);


		qsort(persons, nx, sizeof(Person), (int(*)(const void*, const void*))npcmp);
		Print_Person(persons, nx);

		qsort(persons, nx, sizeof(Person), (int(*)(const void*, const void*))hpcmp);
		Print_Person(persons, nx);

		qsort(persons, nx, sizeof(Person), (int(*)(const void*, const void*))wpcmp);
		Print_Person(persons, nx);
	}


	//str_dump("STRING");

	if (0)
	{
		//printf("%d", str_len_3("Harry"));
		//printf("%d", str_rchar("Harry", 'r'));
		//printf("%d", str_cmp("Harry1", "Harry"));
		//printf("%d", str_ncmp("Hello", "Helr", 4));

		//printf("%d", Boyer_Moore_Match("ILoveYouHarry", "ouHarry"));
		
		if (0)
		{
			char s1[256] = "Harry";
			char s2[256] = "ry";

			char* p = strstr(s1, s2);
			if (p == NULL)
			{
				printf("MOT_MATCHED");
			}
			else
			{
				printf("%d\n", p - s1);
				printf("%s\n", p);
			}
		}

	}

	if (0)
	{
		LinkedList_Menu menu;
		LinkedList list;

		LinkedList_Initialize(&list);
		do
		{
			Member x;
			switch (menu = LinkedList_SelectMenu())
			{
			case ArrayLinkedList_INS_FRONT:
				x = Member_ScanMember("머리에 삽입", MEMBER_NO | MEMBER_NAME);
				LinkedList_InsertFront(&list, &x);
				break;
			case ArrayLinkedList_INS_REAR:
				x = Member_ScanMember("꼬리에 삽입", MEMBER_NO | MEMBER_NAME);
				LinkedList_InsertFront(&list, &x);
				break;
			case ArrayLinkedList_RMV_FRONT:
				LinkedList_RemoveFront(&list);
				break;
			case ArrayLinkedList_RMV_REAR:
				LinkedList_RemoveRear(&list);
				break;
			case ArrayLinkedList_PRINT_CRNT: {
				LinkedList_PrintCurrent(&list);
				break;
			case ArrayLinkedList_RMV_CRNT:
				LinkedList_RemoveCurrent(&list);
				break;
			case ArrayLinkedList_SRCH_NO:
				x = Member_ScanMember("검색", MEMBER_NO);
				if (LinkedList_Search(&list, &x, Member_NoCmp) != NULL)
				{
					LinkedList_PrintLnCurrent(&list);
				}
				else
				{
					puts("그 번호가 없습니다");
				}
				break;
			case ArrayLinkedList_SRCH_NAME:
				x = Member_ScanMember("검색", MEMBER_NAME);
				if (LinkedList_Search(&list, &x, Member_NameCmp) != NULL)
				{
					LinkedList_PrintLnCurrent(&list);
				}
				else
				{
					puts("그 이름의 데이터가 없습니다");
				}
				break;
			case ArrayLinkedList_PRINT_ALL:
				LinkedList_Print(&list);
				break;

			case ArrayLinkedList_CLEAR:
				LinkedList_Clear(&list);
				break;
			}
			}
		} while (menu != ArrayLinkedList_TERMINATE);
		LinkedList_Terminate(&list);
	}

	if (0)
	{
		ArrayLinkedList_Menu menu;
		ArrayLinkedList list;
		ArrayLinkedList_Initialize(&list, 30);
		do
		{
			Member x;
			switch (menu = ArrayLinkedList_SelectMenu())
			{
			case ArrayLinkedList_INS_FRONT:
				x = Member_ScanMember("머리에 삽입", MEMBER_NO | MEMBER_NAME);
				ArrayLinkedList_InsertFront(&list, &x);
				break;
			case ArrayLinkedList_INS_REAR:
				x = Member_ScanMember("꼬리에 삽입", MEMBER_NO | MEMBER_NAME);
				ArrayLinkedList_InsertRear(&list, &x);
				break;
			case ArrayLinkedList_RMV_FRONT:
				ArrayLinkedList_RemoveFront(&list);
				break;
			case ArrayLinkedList_RMV_REAR:
				ArrayLinkedList_RemoveRear(&list);
				break;
			case ArrayLinkedList_PRINT_CRNT:
				ArrayLinkedList_PrintLnCurrent(&list);
				break;
			case ArrayLinkedList_RMV_CRNT:
				LinkedList_RemoveCurrent(&list);
				break;
			case ArrayLinkedList_SRCH_NO:
				x = Member_ScanMember("검색", MEMBER_NO);
				if (ArrayLinkedList_Search(&list, &x, Member_NoCmp) != Null)
				{
					ArrayLinkedList_PrintLnCurrent(&list);
				}
				else
				{
					printf("그 번호의 데이터가 없습니다\n");
				}
				break;
			case ArrayLinkedList_SRCH_NAME:
				x = Member_ScanMember("검색", MEMBER_NAME);
				if (ArrayLinkedList_Search(&list, &x, Member_NameCmp) != Null)
				{
					ArrayLinkedList_PrintLnCurrent(&list);
				}
				else
				{
					printf("그 이름의 데이터가 없습니다\n");
				}
				break;
			case ArrayLinkedList_PRINT_ALL:
				ArrayLinkedList_Print(&list);
				break;
			case ArrayLinkedList_CLEAR:
				ArrayLinkedList_Clear(&list);
				break;
			}
		} while (menu != ArrayLinkedList_TERMINATE);

		ArrayLinkedList_Terminate(&list);
	}

	if (0)
	{
		CircDbLinkedList_Menu menu;
		CircDbLinkedList list;
		CircDbLinkedList_Initialize(&list);
		do
		{
			Member x;
			switch (menu = CircDbLinkedList_SelectMenu())
			{
			case CircDbLinkedList_INS_FRONT:
				x = Member_ScanMember("머리에 삽입", MEMBER_NO | MEMBER_NAME);
				CircDbLinkedList_InsertFront(&list, &x);
				break;
			case CircDbLinkedList_INS_REAR:
				x = Member_ScanMember("꼬리에 삽입", MEMBER_NO | MEMBER_NAME);
				CircDbLinkedList_InsertRear(&list, &x);
				break;
			case CircDbLinkedList_RMV_FRONT:
				CircDbLinkedList_RemoveFront(&list);
				break;
			case CircDbLinkedList_RMV_REAR:
				CircDbLinkedList_RemoveRear(&list);
				break;
			case CircDbLinkedList_PRINT_CRNT:
				CircDbLinkedList_PrintCurrent(&list);
				break;
			case CircDbLinkedList_RMV_CRNT:
				CircDbLinkedList_RemoveCurrent(&list);
				break;
			case CircDbLinkedList_SRCH_NO:
				x = Member_ScanMember("검색", MEMBER_NO);
				if (CircDbLinkedList_Search(&list, &x, Member_NoCmp) != NULL)
				{
					CircDbLinkedList_PrintLnCurrent(&list);
				}
				else
				{
					puts("그 번호의 데이터가 없습니다");
				}
				break;
			case CircDbLinkedList_SRCH_NAME:
				x = Member_ScanMember("검색", MEMBER_NAME);
				if (CircDbLinkedList_Search(&list, &x, Member_NameCmp) != NULL)
				{
					CircDbLinkedList_PrintLnCurrent(&list);
				}
				else
				{
					puts("그 이름의 데이터가 없습니다");
				}
				break;
			case CircDbLinkedList_PRINT_ALL:
				CircDbLinkedList_Print(&list);
				break;
			case CircDbLinkedList_NEXT:
				CircDbLinkedList_Next(&list);
				break;
			case CircDbLinkedList_PREV:
				CircDbLinkedList_Prev(&list);
				break;
			case CircDbLinkedList_CLEAR:
				CircDbLinkedList_Clear(&list);
				break;
			}
		} while (menu != CircDbLinkedList_TERMINATE);
		CircDbLinkedList_Terminate(&list);
	}

	if (1)
	{
		BinTree_Menu menu;
		BinNode* root = NULL;

		do
		{
			Member x;
			BinNode* temp;
			switch (menu = BinTree_SelectMenu())
			{
			case BinTree_ADD:
				x = Member_ScanMember("삽입", MEMBER_NO | MEMBER_NAME);
				root = BinTree_Add(root, &x);
				break;
			case BinTree_REMOVE:
				x = Member_ScanMember("삭제", MEMBER_NO);
				BinTree_Remove(&root, &x);
				break;
			case BinTree_SEARCH:
				x = Member_ScanMember("검색(번호) : ", MEMBER_NO);
				if ((temp = BinTree_Search(root, &x)) != NULL)
				{
					Member_PrintLnMember(&temp->data);
				}
				else
				{
					puts("데이터가 없습니다\n");
				}
				break;
			case BinTree_PRINT:
				puts("모든 노드 출력");
				BinTree_PrintTree(root);
				break;
			}
		} while (menu != BinTree_TERMINATE);

		BinTree_FreeTree(root);
	}
}

