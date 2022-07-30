#include <stdlib.h>
#include "da.h"

static void DA_Reallocate(da_t *da, size_t new_size);

void DA_InitArray(da_t *da, size_t init_size)
{
	if (da == NULL)
	{
		return;
	}

	da->arr = NULL;
	da->capacity = 0;
	da->size = 0;
	if (init_size != 0)
	{
		DA_Reallocate(da, init_size);
	}
}

///@brief resizes the block of the dynamic array
static void DA_Reallocate(da_t *da, size_t new_size)
{
	size_t mem_size = new_size * sizeof(void *);
	// if capacity is 0, then allocate a new block for the first time
	// else resize a previously allocated block
	void **new_block = da->capacity == 0 ? malloc(mem_size) : realloc(da->arr, mem_size);
	if (new_block != NULL)
	{
		da->arr = new_block;
		da->capacity = new_size;
	}
}

///@brief Deinitialize a dynamic array and its allocated memory block
void DA_DeinitArray(da_t *da)
{
	if (da == NULL)
	{
		return;
	}
	// free does nothing to null ptr
	free(da->arr);
	da->capacity = 0;
	da->size = 0;
}

///@brief returns the element that is at specific index i
void *DA_Get(da_t *da, size_t i)
{
	if (da == NULL || i >= da->size)
	{
		return NULL;
	}
	return da->arr[i];
}

///@brief sets an element at a given index i with a new value
void DA_Set(da_t *da, size_t i, void *value)
{
	if (da == NULL || i >= da->size)
	{
		return;
	}
	da->arr[i] = value;
}

///@brief pushes an element at the end of the array and resizes the array if needed
void DA_PushBack(da_t *da, void *value)
{
	if (da == NULL)
	{
		return;
	}
	if (da->size == da->capacity)
	{
		size_t old_cap = da->capacity;
		DA_Reallocate(da, da->capacity == 0 ? 2 : da->capacity * 2);
		if (da->capacity == old_cap) /* re-allocation failed, array size not changed */
		{
			return;
		}
	}
	da->arr[da->size++] = value;
}

///@brief removes an element at a given index i
void DA_Remove(da_t *da, size_t i)
{
	if (da == NULL || i >= da->size)
	{
		return;
	}
	if (da->size > 1)
	{
		for (size_t j = i; j <= da->size - 2; ++j)
		{
			da->arr[j] = da->arr[j + 1];
		}
	}
	da->size--;
}

///@brief returns the size of the dynamic array
size_t DA_Size(da_t *da)
{
	if (da == NULL)
	{
		return 0; // return (size_t)(-1ul) ??
	}
	return da->size;
}