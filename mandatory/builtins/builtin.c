#include "../../includes/minishell.h"
#include <stdio.h>


void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	// Traverse the list and print each node's key and value
	while (current != NULL)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	handle_export(t_container *content)
{
	int	i;

	i = 0;
	while (content->data->cmds[i])
		i++;
	if (i == 1)
		print_export(content);
	else if (i >= 2)
		add_export(content->data->cmds + 1, content);
}
// for the norms 
int	built_in(t_container *content)
{
	if (ft_strcmp (content->data->cmds[0], "env") == 0)
	{
		print_env_list(content->env_list);
		return (0);
	}
	else if (ft_strcmp(content->data->cmds[0], "export") == 0)
	{
		handle_export(content);
		return (0);
	}
	else if (ft_strcmp(content->data->cmds[0], "unset") == 0)
	{
		handle_unset(content->data->cmds, &content->env_list, &content->g_collector);
		return (0);
	}
	else if (ft_strcmp(content->data->cmds[0], "echo") == 0)
	{
		handle_echo(content->data->cmds, &content->g_collector, content->data);
		return (0);
	}
	else if (ft_strcmp(content->data->cmds[0], "pwd") == 0)
	{
		handle_pwd(&content->env_list);
		return (0);
	}
	else if (ft_strcmp(content->data->cmds[0], "cd") == 0)
	{
		handle_cd(content->data->cmds + 1, content);
		return (0);
	}
	else if (ft_strcmp(content->data->cmds[0], "exit") == 0)
		handle_exit(content->data->cmds + 1);
	return (1);
}
