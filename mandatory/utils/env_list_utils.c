/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:26:35 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/20 17:31:59 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*lstnew_env(char *key, char *value, t_gc **g_env_collector, int set)
{
	t_env	*new_node;

	new_node = (t_env *)gc(sizeof(t_env), g_env_collector);
	new_node->key = ft_strdup(key, g_env_collector);
	if (value)
		new_node->value = ft_strdup(value, g_env_collector);
	else
		new_node->value = NULL;
	new_node->print_flag = set;
	new_node->next = NULL;
	return (new_node);
}
void	lstadd_back_env(t_env **lst, t_env *new_t)
{
	t_env	*ptr;
	t_env	*current;

	current = *lst;
	if (!lst || !new_t)
	{
		return ;
	}
	else if (*lst == NULL)
		*lst = new_t;
	else
	{
		ptr = ft_lstlast(current);
		ptr->next = new_t;
	}
}
