
#include "../../includes/minishell.h"

void ft_error(char *msg, char dis,int fd, t_gc **g_collector)
{
    (void)fd;
    if (!msg)
    {
        clear_bin(g_collector);
        return ;
    }
    printf("%s `%c'\n",msg, dis);
    clear_bin(g_collector);
}
