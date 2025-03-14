#include "../../includes/minishell.h"

static void print_pwd_error(t_container *content)
{
	content->status = 1;
	ft_putstr_fd("pwd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access ", 2);
	ft_putstr_fd("parent directories: No such file or directory\n", 2);
}
void	handle_pwd(t_container *content, t_data *current)
{
	t_env *temp;
	char *pwd;
	t_env **env_list;

	env_list = &content->env_list;
	pwd = getcwd(NULL, 0);
    int saved_stdout = rideraction_builtins(current);
	if (pwd == NULL)
	{
		temp = check_if_there("CPWD", env_list);
		if (temp)
			printf("%s\n", temp->value);
		else 
			print_pwd_error(content);
	}
	else
		printf("%s\n", pwd);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}
