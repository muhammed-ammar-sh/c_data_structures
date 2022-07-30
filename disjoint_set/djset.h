#ifndef DJSET_H
#define DJSET_H

#include <stdint.h>

typedef struct _djset_node
{
	struct _djset_node *parent;
	uint32_t rank;
} djset_node_t;

typedef enum
{
	DJSET_CYCLE_NOT_DETECTED = 0,
	DJSET_CYCLE_DETECTED = 1,
} djset_cycle_detection_t;

void DJSet_InitNode(void *node);
void *DJSet_Find(void *node);
djset_cycle_detection_t DJSet_Union(void *a, void *b);
#endif