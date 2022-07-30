#include <stdio.h>
#include "queue.h"

typedef struct
{
	queue_item_t _i;
	int number;
} number_t; // number type that can be queued

int main(void)
{
	queue_t queue;
	Queue_Init(&queue);

	number_t n1 = {.number = 1};
	number_t n2 = {.number = 2};
	number_t n3 = {.number = 3};

	Queue_Enqueue(&queue, &n1);
	Queue_Enqueue(&queue, &n2);
	Queue_Enqueue(&queue, &n3);

	number_t *dequeued_n = Queue_Dequeue(&queue);
	printf("Dequeued number: %d \n", dequeued_n->number);

	dequeued_n = Queue_Dequeue(&queue);
	printf("Dequeued number: %d \n", dequeued_n->number);

	dequeued_n = Queue_Dequeue(&queue);
	printf("Dequeued number: %d \n", dequeued_n->number);

	printf("Queue is empty: %s \n", Queue_IsEmpty(&queue) ? "true" : "false");

	return 0;
}
