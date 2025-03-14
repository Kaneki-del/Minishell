
#include "../../includes/minishell.h"

int	check_builtin_commands(char **commands)
{
	if (commands && commands[0] != NULL)
	{
		if (ft_strcmp(commands[0], "cd") == 0 || ft_strcmp(commands[0],
				"pwd") == 0 || ft_strcmp(commands[0], "export") == 0
			|| ft_strcmp(commands[0], "unset") == 0 || ft_strcmp(commands[0],
				"env") == 0 || ft_strcmp(commands[0], "exit") == 0
			|| ft_strcmp(commands[0], "echo") == 0)
			return (1);
	}
	return (0);
}
