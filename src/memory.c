#include "memory.h"
#include "types.h"

unsigned char memory_block[MEMORY_BLOCK_SIZE];
free_list_node_t *free_list = NULL;

void *malloc(size_t size)
{
  free_list_node_t *current = free_list;
  free_list_node_t *previous = NULL;
  while (current != NULL)
  {
    if (current->size >= size)
    {
      break;
    }
    previous = current;
    current = current->next;
  }

  if (current == NULL)
  {
    return NULL;
  }

  if (current->size > size)
  {
    free_list_node_t *new_node =
        (free_list_node_t *)&memory_block[current->size - size];
    new_node->size = current->size - size;
    new_node->next = current->next;

    current->size = size;
    current->next = new_node;
  }

  if (previous == NULL)
  {
    free_list = current->next;
  }
  else
  {
    previous->next = current->next;
  }

  return (void *)current;
}

void free(void *ptr)
{
  free_list_node_t *node = (free_list_node_t *)ptr;
  node->next = free_list;
  free_list = node;
}
