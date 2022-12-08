#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

#define MEMORY_BLOCK_SIZE 4096

void *malloc(size_t);
void free(void *);

#endif