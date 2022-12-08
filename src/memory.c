#include "memory.h"
#include "types.h"

// The memory block is an array of bytes that will be used for allocation
unsigned char memory_block[MEMORY_BLOCK_SIZE];

// The free_list is a linked list that tracks the free blocks of memory
typedef struct free_list_node {
  size_t size;
  struct free_list_node *next;
} free_list_node_t;

free_list_node_t *free_list = NULL;

// The allocate_memory function attempts to allocate a block of memory
// of the specified size. It returns a pointer to the allocated memory
// or NULL if the allocation fails.
void *malloc(size_t size) {
  // First, we need to find a free block of memory that is large enough
  // to satisfy the request.
  free_list_node_t *current = free_list;
  free_list_node_t *previous = NULL;
  while (current != NULL) {
    if (current->size >= size) {
      // We found a block that is large enough, so we can stop searching.
      break;
    }
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    // We didn't find a large enough block, so the allocation fails.
    return NULL;
  }

  // If the block we found is larger than we need, we can split it into
  // two blocks: one of the desired size, and one that is the remaining
  // space in the original block.
  if (current->size > size) {
    free_list_node_t *new_node =
        (free_list_node_t *)&memory_block[current->size - size];
    new_node->size = current->size - size;
    new_node->next = current->next;

    current->size = size;
    current->next = new_node;
  }

  // If the block we found is exactly the size we need, we can just remove
  // it from the free list.
  if (previous == NULL) {
    free_list = current->next;
  } else {
    previous->next = current->next;
  }

  // Return a pointer to the allocated memory
  return (void *)current;
}

// The free_memory function deallocates a block of memory that was previously
// allocated with allocate_memory.
void free(void *ptr) {
  // Add the block to the front of the free list
  free_list_node_t *node = (free_list_node_t *)ptr;
  node->next = free_list;
  free_list = node;
}
