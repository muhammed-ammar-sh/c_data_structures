#include <stdio.h>
#include "da.h"

static void PrintAllDynamicArrayElements(da_t *da);

int main(void)
{
	int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

	da_t da;
	DA_InitArray(&da, 2);

	DA_PushBack(&da, &i1);
	DA_PushBack(&da, &i2);
	DA_PushBack(&da, &i3);
	DA_PushBack(&da, &i4);
	PrintAllDAElements(&da);

	DA_Set(&da, 0, &i5);
	PrintAllDAElements(&da);

	DA_Remove(&da, 1);
	PrintAllDAElements(&da);

	DA_Remove(&da, 1);
	PrintAllDAElements(&da);

	DA_Remove(&da, 1);
	PrintAllDAElements(&da);

	DA_Remove(&da, 0);
	PrintAllDAElements(&da);

	DA_DeinitArray(&da);

	return 0;
}

static void PrintAllDynamicArrayElements(da_t *da)
{
	printf("Dynamic array elements: ");
	for (size_t i = 0; i < DA_Size(da); i++)
	{
		printf("%d, ", *(int *)DA_Get(da, i));
	}
	printf("\n");
}