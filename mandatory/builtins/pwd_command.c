#include "../../includes/minishell.h"

void	handle_pwd(t_env **env_list, t_data *current)
{
	t_env *temp;
    int saved_stdout = rideraction_builtins(current);
	char buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		temp = check_if_there("PWD", env_list);
		if (temp)
			printf("%s\n", temp->value);
	}
	else
		printf("%s\n", buffer);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}
