
#include "../../includes/minishell.h"


void type_flag(t_env *current_old, t_env **new_node, t_container *content)
{
	if (current_old->print_flag != 0)
			*new_node = lstnew_env(current_old->key, current_old->value,
					&content->g_collector, 1);
		else
			*new_node = lstnew_env(current_old->key, current_old->value,
					&content->g_collector, 0);
}

t_env	*copy_list(t_container *content)
{
	t_env	*new_head;
	t_env	*current_old;
	t_env	*current_new;
	t_env	*new_node;

	if (!content->env_list)
		return (NULL);
	if (content->env_list->print_flag != 0)
		new_head = lstnew_env(content->env_list->key, content->env_list->value,
				&content->g_collector, 1);
	else
		new_head = lstnew_env(content->env_list->key, content->env_list->value,
				&content->g_collector, 0);
	current_old = content->env_list->next;
	current_new = new_head;
	while (current_old)
	{
		type_flag(current_old, &new_node, content);
		current_new->next = new_node;
		current_new = new_node;
		current_old = current_old->next;
	}
	return (new_head);
}

t_env	*find_smallest(t_env *head)
{
	t_env	*smallest;
	t_env	*current;

	if (!head)
		return (NULL);
	smallest = head;
	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, smallest->key) < 0)
			smallest = current;
		current = current->next;
	}
	return (smallest);
}
void	delete_node(t_env **list_env, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *list_env;
	prev = NULL;
	// Check if the first node is the one to delete
	if (temp && ft_strcmp(temp->key, key) == 0)
	{
		*list_env = temp->next;
		return ;
	}
	// Traverse the list to find the node to delete
	while (temp && ft_strcmp(temp->key, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	// If the node wasn't found, return
	if (!temp)
		return ;
	// Unlink the node and free it
	prev->next = temp->next;
}
/*void	print_export(t_data *current ,t_container *content)
{
	while (temp)
	{
		// Print the key and value of the smallest element
		if (smallest->key && smallest->value)
			printf("declare -x %s=\"%s\"\n", smallest->key, smallest->value);
		else if (!smallest->value)
			printf("declare -x %s\n", smallest->key);
		// Delete the smallest node from the list
		delete_node(&temp, smallest->key);
			// Ensure temp is updated after deletion
	}
*/
void	print_key_value(t_env *smallest)
{
	if (smallest->key && smallest->value)
	{
		printf("declare -x %s=\"%s\"\n", smallest->key, smallest->value);
	}
	else if (!smallest->value)
		printf("declare -x %s\n", smallest->key);
}
void filter_print(t_env *smallest)
{
	if (smallest->key && smallest->value && smallest->print_flag == 0
			&& ft_strcmp(smallest->key, "_"))
			print_key_value(smallest);
		else if (!smallest->value && smallest->print_flag == 0
			&& ft_strcmp(smallest->key, "_"))
			printf("declare -x %s\n", smallest->key);
}
void	print_export(t_data *current, t_container *content)
{
	t_env	*smallest;
	int		saved_stdout;

	saved_stdout = rideraction_builtins(current); // Store original stdout
	if (!content->env_list)
		return ;
	t_env *temp = copy_list(content); // Start from the head
	while (temp)
	{
		smallest = NULL;
		smallest = find_smallest(temp); // Find the smallest element in the list
		if (!smallest)                  // Safety check
			return ;
		filter_print(smallest);
		delete_node(&temp, smallest->key);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
	content->status = 0;
}
