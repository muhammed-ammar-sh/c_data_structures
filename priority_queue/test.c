#include "prio_queue.h"
#include <stdio.h>

typedef struct
{
	char *name;
	uint8_t priority;
} thread_t;

///@brief function to compare two threads priorities, returns positive value 
///       if thread a's priority is higher than thread b's priority
int CompareThreads(const void *a, const void *b)
{
	thread_t *a_thread = (thread_t *)a, *b_thread = (thread_t *)b;
	return a_thread->priority - b_thread->priority;
}

#define MAX_THREADS_COUNT 10

int main(void)
{
	thread_t prio_queue_array[MAX_THREADS_COUNT] = {{.priority = 0}};

	prio_queue_t queue;
	PrioQueue_Init(&queue, prio_queue_array, MAX_THREADS_COUNT, sizeof(thread_t), CompareThreads);

	thread_t t1 = {.name = "Thread 1", .priority = 1};
	PrioQueue_Insert(&queue, &t1);

	thread_t t2 = {.name = "Thread 2", .priority = 2};
	PrioQueue_Insert(&queue, &t2);

	thread_t t3 = {.name = "Thread 3", .priority = 3};
	PrioQueue_Insert(&queue, &t3);

	thread_t *highest_priority_thread = PrioQueue_ExtractMax(&queue);
	printf("Extracted thead with highest priority: \"%s\", priority = %d\n",
		   highest_priority_thread->name, highest_priority_thread->priority);
	// Extracted thead with highest priority: "Thread 3", priority = 3


	highest_priority_thread = PrioQueue_ExtractMax(&queue);
	printf("Extracted thead with highest priority: \"%s\", priority = %d\n",
		   highest_priority_thread->name, highest_priority_thread->priority);
	// Extracted thead with highest priority: "Thread 2", priority = 2


	thread_t t4 = {.name = "Thread 4", .priority = 4};
	PrioQueue_Insert(&queue, &t4);
	highest_priority_thread = PrioQueue_ExtractMax(&queue);
	printf("Extracted thead with highest priority: \"%s\", priority = %d\n",
		   highest_priority_thread->name, highest_priority_thread->priority);
	// Extracted thead with highest priority: "Thread 4", priority = 4

	return 0;
}
