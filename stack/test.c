#include <stdio.h>
#include "stack.h"

typedef struct
{
	stack_item_t _i;
	float temperature;
} temperature_t;

int main(void)
{
	stack_t stack;
	Stack_Init(&stack);

	temperature_t t1 = {.temperature = 12.2f};
	temperature_t t2 = {.temperature = 13.1f};
	temperature_t t3 = {.temperature = 14.5f};

	Stack_Push(&stack, &t1); // stack : t1
	Stack_Push(&stack, &t2); // stack : t2 -> t1
	Stack_Push(&stack, &t3); // stack : t3 -> t2 -> t1

	printf("Stack is empty: %s \n", Stack_IsEmpty(&stack) ? "true" : "false");

	temperature_t *popped_t = Stack_Pop(&stack); // stack : t2 -> t1
	printf("Popped temperature: %.2f \n", popped_t->temperature);

	popped_t = Stack_Pop(&stack); // stack : t1
	printf("Popped temperature: %.2f \n", popped_t->temperature);

	popped_t = Stack_Pop(&stack); // stack :
	printf("Popped temperature: %.2f \n", popped_t->temperature);

	printf("Stack is empty: %s \n", Stack_IsEmpty(&stack) ? "true" : "false");

	return 0;
}
