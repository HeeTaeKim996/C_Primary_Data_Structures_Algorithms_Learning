#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sortings.h"
#include "time.h"
#include "StringMatch.h"
#include "Member.h"
#include "LinkedList.h"

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
} Menu;

Menu SelectMenu(void)
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
	return (Menu)ch;
}
/*
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

	if (1)
	{
		Menu menu;
		LinkedList list;

		LinkedList_Initialize(&list);
		do
		{
			Member x;
			switch (menu = SelectMenu())
			{
			case INS_FRONT:
				x = Member_ScanMember("머리에 삽입", MEMBER_NO | MEMBER_NAME);
				LinkedList_InsertFront(&list, &x);
				break;
			case INS_REAR:
				x = Member_ScanMember("꼬리에 삽입", MEMBER_NO | MEMBER_NAME);
				LinkedList_InsertFront(&list, &x);
				break;
			case RMV_FRONT:
				LinkedList_RemoveFront(&list);
				break;
			case RMV_REAR:
				LinkedList_RemoveRear(&list);
				break;
			case PRINT_CRNT: {
				LinkedList_PrintCurrent(&list);
				break;
			case RMV_CRNT:
				LinkedList_RemoveCurrent(&list);
				break;
			case SRCH_NO:
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
			case SRCH_NAME:
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
			case PRINT_ALL:
				LinkedList_Print(&list);
				break;

			case CLEAR:
				LinkedList_Clear(&list);
				break;
			}
			}
		} while (menu != TERMINATE);
		LinkedList_Terminate(&list);
	}
}
*/
