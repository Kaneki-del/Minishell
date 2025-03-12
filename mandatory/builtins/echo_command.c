#include "../../includes/minishell.h"

void	echo(char **cmd)
{
	int	i;
	int	new_line;
	int	espace;

	espace = 0;
	new_line = 0;
	i = 0;
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

void	handle_echo(char **cmd, t_data *list)
{
	int	i;
	int	saved_stdout;

	saved_stdout = rideraction_builtins(list); // Store original stdout
	i = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
		echo(cmd + 1);
	else
		write(1, "\n", 1);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}
