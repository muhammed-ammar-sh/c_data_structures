#ifndef DA_H
#define DA_H

#include <stdint.h>
typedef struct
{
	void **arr;
	size_t capacity;
	size_t size;
} da_t;

void DA_InitArray(da_t *da, size_t init_size);
void DA_DeinitArray(da_t *da);
void *DA_Get(da_t *da, size_t i);
void DA_Set(da_t *da, size_t i, void *value);
void DA_PushBack(da_t *da, void *value);
void DA_Remove(da_t *da, size_t i);
size_t DA_Size(da_t *da);

#endif