/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:54:52 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/16 16:09:21 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*find_smallest(t_env *head)
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
	if (temp && ft_strcmp(temp->key, key) == 0)
	{
		*list_env = temp->next;
		return ;
	}
	while (temp && ft_strcmp(temp->key, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
}

void	print_key_value(t_env *smallest)
{
	if (smallest->key && smallest->value)
		printf("declare -x %s=\"%s\"\n", smallest->key, smallest->value);
	else if (!smallest->value)
		printf("declare -x %s\n", smallest->key);
}

static void	filter_print(t_env *smallest)
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
	t_env	*temp;

	saved_stdout = rideraction_builtins(current);
	if (!content->env_list)
		return ;
	temp = copy_list(content);
	while (temp)
	{
		smallest = NULL;
		smallest = find_smallest(temp);
		if (!smallest)
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
