
#include "../../includes/minishell.h"

void	echo(char **cmd, t_gc **gc)
{
	int		i;
	int		new_line;
	t_env	*temp;
	int		espace;

	(void)gc;
	espace = 0;
	new_line = 0;
	i = 0;
	temp = NULL;
	if (ft_strcmp(cmd[i], "-n") == 0)
	{
		i++;
		new_line = 1;
	}
	while (cmd[i])
	{
		if (espace == 1)
			write(1, " ", 1);
		ft_putstr_fd(cmd[i], 1);
		espace = 1;
		i++;
	}
	if (new_line == 0)
		write(1, "\n", 1);
}

void	handle_echo(char **cmd, t_gc **gc, t_data *list)
{
	int new_fd;
	(void)gc;

	if ((list->out_fd != 0))
		close(list->out_fd);
	if (list->in_fd != 0)
	{
		new_fd
	}
		

	int i = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
		echo(cmd + 1, gc);
}
