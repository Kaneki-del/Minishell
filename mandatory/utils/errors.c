
#include "../../includes/minishell.h"

void ft_error(char *msg, char *dis, int fd, t_gc **g_collector)
{
    (void)fd;
    if (!msg)
    {
        clear_bin(g_collector);
        return ;
    }
    ft_putstr_fd(msg, fd);
    ft_putstr_fd(" `", fd);
    ft_putstr_fd(dis, fd);
    ft_putstr_fd("'\n", fd);
    clear_bin(g_collector);
}
void ft_error_exec(char *msg, char *dis, char *left, int fd)
{
    (void)fd;
    if (!msg)
        return ;
    ft_putstr_fd(msg, fd);
    ft_putstr_fd(" `", fd);
    ft_putstr_fd(dis, fd);
    ft_putstr_fd("'", fd);
    ft_putstr_fd(left, fd);
    ft_putstr_fd("\n", fd);
}
