#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

#define MEMORY_BLOCK_SIZE 4096

typedef struct free_list_node
{
    size_t size;
    struct free_list_node *next;
} free_list_node_t;

void *malloc(size_t);
void free(void *);

#endif