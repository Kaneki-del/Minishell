
#include "../../includes/minishell.h"

void echo(char **cmd, t_gc **gc)
{
	(void)gc;
	int	i;
    int new_line;
	t_env	*temp;

	i = 0;
	temp = NULL;
    if (ft_strcmp(cmd[i], "-n"))
    {
        i++;
        new_line = 1;
    }
	while (cmd[i])
	{
        printf("i am here");
        ft_putstr_fd(cmd[i], 1);
        i++;
	}
    if (new_line == 1)
        write(1, "\n", 1);
}
void handle_echo(char **cmd, t_gc **gc)
{
	(void)gc;
    int i  = 0;
    while (cmd[i])
        i++;
    if (i >= 2)
      echo(cmd + 1,gc);
}