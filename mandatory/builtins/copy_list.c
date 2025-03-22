/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:58:46 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 15:05:11 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	type_flag(t_env *current_old, t_env **new_node,
		t_container *content)
{
	if (current_old->print_flag != 0)
		*new_node = lstnew_env(current_old->key, current_old->value,
				content, 1);
	else
		*new_node = lstnew_env(current_old->key, current_old->value,
				content, 0);
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
				content, 1);
	else
		new_head = lstnew_env(content->env_list->key, content->env_list->value,
				content, 0);
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
