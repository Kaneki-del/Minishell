/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:26:35 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/26 01:46:33 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*lstnew_env(char *key, char *value, t_container *content, int set)
{
	t_env	*new_node;

	new_node = (t_env *)gc(sizeof(t_env), &content->g_env_collector, content);
	new_node->key = ft_strdup(key, &content->g_env_collector, content);
	if (value)
		new_node->value = ft_strdup(value, &content->g_env_collector, content);
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

void	get_pwd_part3(t_container *content, t_env **env_list)
{
	t_env	*cpwd;
	t_env	*ccpwd;

	cpwd = check_if_there("PWD", env_list);
	ccpwd = check_if_there("CPWD", env_list);
	if (cpwd != NULL && cpwd->value != NULL)
	{
		if (ccpwd != NULL)
		{
			ccpwd->print_flag = 3;
			ccpwd->value = ft_strdup(cpwd->value, &content->g_env_collector,
					content);
		}
		else
			lstadd_back_env(env_list, lstnew_env("CPWD", cpwd->value, content,
					3));
	}
}
