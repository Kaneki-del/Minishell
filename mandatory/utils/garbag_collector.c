
#include "../../includes/minishell.h"

t_gc *gc_node(t_gc **garbage_list) {
    t_gc *last_node;

    if (!garbage_list ) // add check here for the head of garbage list
        return (NULL);
    last_node = *garbage_list;
    if (last_node == NULL)
        return (*garbage_list = ft_calloc(sizeof(char), sizeof(t_gc)));
    while (last_node && last_node->next)
        last_node = last_node->next;

    return (last_node->next = ft_calloc(sizeof(char), sizeof(t_gc)));
}

void clear_bin(t_gc **garbage_list)
{
    t_gc *current;
    t_gc *next;

    if (!garbage_list) // shoud add a check here hor the first element *garbage_list
        return;
    current = *garbage_list;
    next = NULL;
    while (current)
    {
        next = current->next;
        free(current->adress);
        free(current);
        // current->adress = NULL;
        current = NULL;
        current = next;
    }
    garbage_list = NULL;
}
void *gc(size_t size, t_gc **garbage_list)
{
    t_gc *new_garbage_node;
    void *allocated;

    new_garbage_node = NULL;
    allocated = ft_calloc(sizeof(char), size);
    if (allocated == NULL)
    {
        clear_bin(garbage_list);
        write(2, "allocation failed!", 17);
    }
    new_garbage_node = gc_node(garbage_list);
    if (new_garbage_node == NULL)
    {
        clear_bin(garbage_list);
        write(2, "allocation failed!", 17);
        exit(EXIT_FAILURE);
    }
    new_garbage_node->adress = allocated;
    new_garbage_node->next = NULL;
    return (allocated);
}
