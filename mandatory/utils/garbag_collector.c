#include "../../includes/execution.h"

// this function is responsbel to create the node that store the allocated
// adress
t_gc *gc_node(t_gc **garbage_list) {
  t_gc *last_node;
  last_node = *garbage_list;
  if (last_node == NULL)
    return (*garbage_list = calloc(sizeof(char), sizeof(t_gc)));
  while (last_node && last_node->next)
    last_node = last_node->next;
  return (last_node->next = calloc(sizeof(char), sizeof(t_gc)));
}
void clear_bin(t_gc **garbage_list) {
  t_gc *current;
  t_gc *next;
  if (!garbage_list)
    return;
  current = *garbage_list;
  while (current) {
    next = current->next;
    free(current->adress);
    free(current);
    current = next;
  }
  garbage_list = NULL;
}
void *gc(size_t size, t_gc **garbage_list) {

  t_gc *new_garbage_node;
  void *allocated;

  allocated = calloc(sizeof(char), size);
  if (allocated == NULL) {
    clear_bin(garbage_list);
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  new_garbage_node = gc_node(garbage_list);
  if (new_garbage_node == NULL) {
    clear_bin(garbage_list);
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  new_garbage_node->adress = allocated;
  new_garbage_node->next = NULL;
  return allocated;
}
