#include "../../includes/minishell.h"

void	handle_pwd(t_env **env_list, t_data *current)
{
	t_env *temp;
	char *pwd;

	pwd = getcwd(NULL, 0);
    int saved_stdout = rideraction_builtins(current);

	if (pwd == NULL)
	{
		temp = check_if_there("CPWD", env_list);
		if (temp)
			printf("%s\n", temp->value);
		else 
			printf("shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	}
	else
		printf("%s\n", pwd);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}
