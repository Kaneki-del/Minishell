#include "../../includes/minishell.h"
#include <stdio.h>


void	print_env_list(t_env *env_list, t_data *list)
{
	t_env	*current;
	int saved_stdout = rideraction_builtins(list); // Store original stdout

	current = env_list;
	// Traverse the list and print each node's key and value
	while (current != NULL)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
	
}

int	handle_export(t_data *current ,t_container *content)
{
	int	i;

	i = 0;
	while (current->cmds[i])
		i++;
	if (i == 1)
	{
		print_export(current ,content);
		return 0;
	}
	return(add_export(content->data->cmds + 1, content));

}
// for the norms 
int	built_in(t_data *current, t_container *content)
{
	if (ft_strcmp (content->data->cmds[0], "env") == 0)
	{
		print_env_list(content->env_list, content->data);
		return (0);
	}
	else if (ft_strcmp(current->cmds[0], "export") == 0)
		return handle_export(current, content);
	else if (ft_strcmp(current->cmds[0], "unset") == 0)
		return (handle_unset(current->cmds, &content->env_list, current));
	else if (ft_strcmp(current->cmds[0], "echo") == 0)
		return (handle_echo(current->cmds, current), 0);
	else if (ft_strcmp(current->cmds[0], "pwd") == 0)
		return  (handle_pwd(&content->env_list, current), 0);
	else if (ft_strcmp(current->cmds[0], "cd") == 0)
		return handle_cd(current->cmds + 1, content);
	else if (ft_strcmp(current->cmds[0], "exit") == 0)
		return handle_exit(content->data->cmds + 1, content);
	return (1);
}
