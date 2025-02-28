#include "../../includes/minishell.h"


void clean_fds(t_data *list)
{
    t_data *current;
    current = list;
    while (current)
    {
        if (current->out_fd != 0)
            close(current->out_fd);
        if (current->in_fd != 0)
            close(current->in_fd);
        current = current->next;
    }
}
