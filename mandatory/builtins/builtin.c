#include "../../includes/minishell.h"
#include <stdio.h>

void	print_env_list(t_container *content, t_data *list)
{
	t_env	*current;
	int		saved_stdout;

	saved_stdout = rideraction_builtins(list); // Store original stdout
	current = content->env_list;
	while (current != NULL)
	{
		if (current->key && current->value && current->print_flag == 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	handle_export(t_data *current, t_container *content)
{
	int	i;

	i = 0;
	while (current->cmds[i])
		i++;
	if (i == 1)
		print_export(current, content);
	else
		add_export(content->data->cmds + 1, content);
}

// for the norms
void	built_in(t_data *current, t_container *content)
{
	if (ft_strcmp(content->data->cmds[0], "env") == 0)
		print_env_list(content, content->data);
	else if (ft_strcmp(current->cmds[0], "export") == 0)
		handle_export(current, content);
	else if (ft_strcmp(current->cmds[0], "unset") == 0)
		handle_unset(current->cmds, content, current);
	else if (ft_strcmp(current->cmds[0], "echo") == 0)
		handle_echo(current->cmds, current);
	else if (ft_strcmp(current->cmds[0], "pwd") == 0)
		handle_pwd(content, current);
	else if (ft_strcmp(current->cmds[0], "cd") == 0)
		handle_cd(current->cmds + 1, content);
	else if (ft_strcmp(current->cmds[0], "exit") == 0)
		handle_exit(current, content);
}
