#include "../../includes/minishell.h"


void clean_fds(t_data *list)
{
    if (list->out_fd != 0)
        close(list->out_fd);
    if (list->in_fd != 0)
        close(list->out_fd);
}