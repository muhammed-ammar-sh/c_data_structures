#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "static_heap.h"

int IsGreater(const void *a, const void *b)
{
	return *(intptr_t *)a - *(intptr_t *)b;
}

int IsLower(const void *a, const void *b)
{
	return *(intptr_t *)b - *(intptr_t *)a;
}

void PrintHeapArray(int *arr, size_t arr_size);

int main(void)
{
	srand(time(0));

#define HEAP_SIZE 20
	int a[HEAP_SIZE]; // will hold the max heap nodes
	int b[HEAP_SIZE]; // will hold the min heap nodes
	
	// generate random unsorted numbers
	puts("Unsorted heap array");
	for (int i = 0; i < HEAP_SIZE; i++)
	{
		b[i] = a[i] = rand() % HEAP_SIZE;
		printf("%02d, ", a[i]);
	}

	puts("\n\n");

	static_heap_t max_heap;
	StaticHeap_InitHeap(&max_heap, a, HEAP_SIZE, HEAP_SIZE, sizeof(a[0]), (void *)INT_MAX, IsGreater);
	StaticHeap_BuildHeap(&max_heap);
	puts("Max heap array nodes ...");
	PrintHeapArray(a, HEAP_SIZE);

	static_heap_t min_heap;
	StaticHeap_InitHeap(&min_heap, b, HEAP_SIZE, HEAP_SIZE, sizeof(b[0]), (void *)INT_MIN, IsLower);
	StaticHeap_BuildHeap(&min_heap);
	puts("Min heap array nodes ...");
	PrintHeapArray(b, HEAP_SIZE);

	return 0;
}

void PrintHeapArray(int *arr, size_t arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		printf("%02d. node= %02d, ", i, arr[i]);

		if (LEFT_CHILD_IDX(i) < arr_size)
		{
			printf("Left= %02d, ", arr[LEFT_CHILD_IDX(i)]);
		}
		else
		{
			printf("Left= na, ");
		}

		if (RIGHT_CHILD_IDX(i) < arr_size)
		{
			printf("Right: %02d \n", arr[RIGHT_CHILD_IDX(i)]);
		}
		else
		{
			printf("Right= na \n");
		}
	}
	puts("\n\n");
}