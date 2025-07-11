#include <stdlib.h>
#pragma once

/*
BubbleSort		: ��������. ���� �־�. ���������� ���

SelectionSort	: ��������(����Ƽ�� ���������� �ƴ϶� �ϴµ�, �ڵ� ���� ��������). ��Ҽ��� ���� ���Ŀ��� ȿ������ ����

InsertionSort	: ��������. ��Ҽ��� ���� ���Ŀ��� ȿ�����̸�, ������ ���� �ϼ��� ������ ���Ŀ��� ���� �ְ�

ShellSort		: �Ҿ�������. QuickSort ���� ������, ���� ������ ���� �Ҿ��� ����

QuickSort		: �Ҿ�������. ��������� ���� ���� �Ҿ��� ���� (�־��� ���� O(n^2))

MergeSort		: ��������. ��Ҽ��� ���� ���� ���� �� ���� ����

HeapSort		: �Ҿ�������. ���� ��ɿ��� ȿ���� ���� ������, ����Ʈ�� �����̱� ������,  
                  ����, ���� Top5�� �켱���� ť���� ȿ���� ����

CountingSort	: ��������. [0�̻��� �������� �ϰ�, ��ҿ� ������ ū ��Ż���� ����, max���� �˾ƾ� �Ѵٴ�] ���� �Ͽ�, 
				  QuickSort���ٵ� ���� ������ ���� ��������

*/

#define swap(type, x, y) do{type t = x; x = y; y = t;} while(0)


/*----------------------------
	      BubbleSort
----------------------------*/
inline void BubbleSort(int array[], int n)
{
	int k = 0;

	while (k < n - 1)
	{
		int last = n - 1;

		for (int i = n - 1; i > k; i--)
		{
			if (array[i - 1] > array[i])
			{
				swap(int, array[i - 1], array[i]);
				last = i;
			}
		}

		k = last;
	}
}

/*--------------------------
        SelectionSort
--------------------------*/
inline void SelectionSort(int array[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (array[minIndex] > array[j])
			{
				minIndex = j;
			}
		}
		swap(int, array[i], array[minIndex]);
	}
}

/*------------------------
	   InsertionSort
------------------------*/
inline void InsertionSort(int array[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int tmp = array[i];
		int j = i;
		for (; j > 0 && array[j - 1] > tmp; j--)
		{
			array[j] = array[j - 1];
		}
		array[j] = tmp;
	}
}

/*------------------------
        ShellSort
------------------------*/
inline void ShellSort(int array[], int n)
{
	int h = 1;
	while (h < n)
	{
		h = 3 * h + 1;
	}
	h /= 3;

	for (; h > 0; h /= 3)
	{
		for (int i = h; i < n; i++)
		{
			int tmp = array[i];
			int j = i;
			for (; j >= h && array[j - h] > tmp; j -= h)
			{
				array[j] = array[j - h];
			}
			array[j] = tmp;
		}
	}
}
/*---------------------
       QuickSort
----------------------*/
#include "IntStack.h"
inline void QuickSort(int array[], int n)
{
	IntStack lStack;
	IntStack rStack;

	IntStack_Initialize(&lStack, n);
	IntStack_Initialize(&rStack, n);

	int left = 0;
	int right = n - 1;

	IntStack_Push(&lStack, left);
	IntStack_Push(&rStack, right);

	while (!IntStack_IsEmpty(&lStack))
	{
		IntStack_Pop(&lStack, &left);
		IntStack_Pop(&rStack, &right);

		int mid = (left + right) / 2;

		if (array[left] > array[mid])
		{
			swap(int, array[left], array[mid]);
		}
		if (array[mid] > array[right])
		{
			swap(int, array[mid], array[right]);
		}
		if (array[left] > array[mid])
		{
			swap(int, array[left], array[mid]);
		}

		int pivot = array[mid];
		swap(int, array[mid], array[right - 1]);

		int pl = left + 1;
		int pr = right - 2;

		do
		{
			while (array[pl] < pivot)
			{
				pl++;
			}
			while (array[pr] > pivot)
			{
				pr--;
			}

			if (pl <= pr)
			{
				swap(int, array[pl], array[pr]);
				pl++;
				pr--;
			}
		} while (pl <= pr);

		if (left < pr)
		{
			IntStack_Push(&lStack, left);
			IntStack_Push(&rStack, pr);
		}
		if (pl < right)
		{
			IntStack_Push(&lStack, pl);
			IntStack_Push(&rStack, right);
		}
	}

	IntStack_Terminate(&lStack);
	IntStack_Terminate(&rStack);
}


/*----------------------
        MergeSort
----------------------*/
inline void __MergeSort(int array[], int* buffer, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;

		__MergeSort(array, buffer, left, center);
		__MergeSort(array, buffer, center + 1, right);


		int enqueArray = left;
		int dequeArray = left;
		int enqueBuffer = 0;
		int dequeBuffer = 0;

		for(; dequeArray <= center; dequeArray++)
		{
			buffer[enqueBuffer++] = array[dequeArray];
		}
		while (dequeArray <= right && dequeBuffer < enqueBuffer)
		{
			array[enqueArray++] = buffer[dequeBuffer] <= array[dequeArray] ? buffer[dequeBuffer++] : array[dequeArray++];
		}
		while (dequeBuffer < enqueBuffer)
		{
			array[enqueArray++] = buffer[dequeBuffer++];
		}
	}
}


inline int MergeSort(int array[], int n)
{
	int* buffer;
	if ((buffer = calloc(n, sizeof(int))) == NULL)
	{
		return -1;
	}

	__MergeSort(array, buffer, 0, n - 1);

	free(buffer);
	return 0;
}

/*----------------------
        HeapSort
----------------------*/
inline void __HeapSort(int array[], int left, int right)
{
	int tmp = array[left];
	int parent = left;
	int child;

	for (; parent < (right + 1) / 2; parent = child)
	{
		int cl = 2 * parent + 1;
		int cr = cl + 1;

		child = (cr <= right && array[cr] > array[cl]) ? cr : cl;

		if (tmp >= array[child])
		{
			break;
		}
		array[parent] = array[child];
	}
	array[parent] = tmp;
}
inline void HeapSort(int array[], int n)
{
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		__HeapSort(array, i, n - 1);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(int, array[0], array[i]);
		__HeapSort(array, 0, i - 1);
	}
}

/*-----------------------
       CountingSort
-----------------------*/
inline void CountingSort(int array[], int max, int n)
{
	int* frequencyTable = calloc(max + 1, sizeof(int));
	int* copied = calloc(n, sizeof(int));

	for (int i = 0; i <= max; i++) frequencyTable[i] = 0;
	for (int i = 0; i < n; i++) frequencyTable[array[i]]++;
	for (int i = 1; i <= max; i++) frequencyTable[i] += frequencyTable[i - 1];
	for (int i = n - 1; i >= 0; i--) copied[--frequencyTable[array[i]]] = array[i];
	for (int i = 0; i < n; i++) array[i] = copied[i];

	free(frequencyTable);
	free(copied);
}


/*-----------------
	   ETC
-----------------*/


inline void QuickSort_1(int array[], int left, int right)
{
	int pl = left;
	int pr = right;
	int x = array[(left + right) / 2];


	if (1)
	{
		printf("arr[%d] ~ arr[%d] : { ", left, right);
		for (int i = left; i < right; i++)
		{
			printf("%d ", array[i]);
		}
		printf("%d }\n", array[right]);
		printf("Pivot : %d\n", array[x]);
	}

	do
	{
		while (array[pl] < x)
		{
			pl++;
		}
		while (array[pr] > x)
		{
			pr--;
		}
		if (pl <= pr)
		{
			swap(int, array[pl], array[pr]);
			pl++;
			pr--;
		}
	} while (pl <= pr);

	if (left < pr)
	{
		QuickSort_1(array, left, pr);
	}
	if (pl < right)
	{
		QuickSort_1(array, pl, right);
	}
}

#include "IntStack.h"
inline void QuickSort_2(int array[], int left, int right)
{
	IntStack lStack;
	IntStack rStack;

	IntStack_Initialize(&lStack, right - left + 1);
	IntStack_Initialize(&rStack, right - left + 1);

	IntStack_Push(&lStack, left);
	IntStack_Push(&rStack, right);

	while (!IntStack_IsEmpty(&lStack))
	{
		int pl = (IntStack_Pop(&lStack, &left), left);
		/* �� type instance = ( A, B);
			-> ���� Ʃ���� �ƴ�, (A, B);���� A�� ���� ������, B�� ��ȯ�϶�� �ڵ��,
			instance �� B�� �Ҵ�ȴ�.
			�� �ڵ��

		IntStack_Pop(&lStack, &left);
		int pl = left;

		�� ������ ������ �ڵ��.
		C++������ �����ϰ� �����ϴ� ����
		*/


		int pr = (IntStack_Pop(&rStack, &right), right);
		int x = array[(left + right) / 2];

		do
		{
			while (array[pl] < x)
			{
				pl++;
			}
			while (array[pr] > x)
			{
				pr--;
			}

			if (pl <= pr)
			{
				swap(int, array[pl], array[pr]);
				pl++;
				pr--;
			}
		} while (pl <= pr);

		if (left < pr)
		{
			IntStack_Push(&lStack, left);
			IntStack_Push(&rStack, pr);
		}
		if (pl < right)
		{
			IntStack_Push(&lStack, pl);
			IntStack_Push(&rStack, right);
		}
	}

	IntStack_Terminate(&lStack);
	IntStack_Terminate(&rStack);
}


inline void QuickSort_3(int array[], int left, int right)
{
	/*
	��
	   Pivot�� mid�� right -1 �� ���ΰ� �����ϰ�, �������ķ� left, right mid�� ������, �ݺ����Ŀ����� �� ���� ���ܽ�Ų�ٴ�
	   ���� �����ߴ�. �׷��� mid right-1�� ������, ����ġ ��Ű�� �ʾƵ�, ������ ���� �κ��� �������� ���ߴ�.
	   �ݺ�ȣ���� ����������, right - ���� ���� ���� ���� �� �ƴѰ�? �Ӹ� ������.. ���� ���ߴ�.
	*/


	int mid = (left + right) / 2;

	if (array[left] > array[mid])
	{
		swap(int, array[left], array[mid]);
	}
	if (array[mid] > array[right])
	{
		swap(int, array[mid], array[right]);
	}
	if (array[left] > array[mid])
	{
		swap(int, array[left], array[mid]);
	}

	int x = array[mid];
	swap(int, array[mid], array[right - 1]);

	int pl = left + 1;
	int pr = right - 2;

	do
	{
		while (array[pl] < x)
		{
			pl++;
		}
		while (array[pr] > x)
		{
			pr--;
		}

		if (pl <= pr)
		{
			swap(int, array[pl], array[pr]);
			pl++;
			pr--;
		}

	} while (pl <= pr);


	if (left < pr)
	{
		QuickSort_3(array, left, pr);
	}
	if (pl < right)
	{
		QuickSort_3(array, pl, right);
	}
}

