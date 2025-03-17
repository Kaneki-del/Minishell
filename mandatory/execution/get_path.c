/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:52:05 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/16 13:53:40 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_path(t_container *content)
{
	char	*env_path;
	t_env	*current;

	current = NULL;
	current = content->env_list;
	env_path = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
		{
			if (current->value)
				env_path = ft_strdup(current->value, &content->g_collector);
			if (env_path == NULL)
				return (NULL);
		}
		current = current->next;
	}
	return (env_path);
}

char	**get_path(t_container *content)
{
	char	*path_value;
	char	**path_list;

	path_value = get_env_path(content);
	if (!path_value)
		return (NULL);
	path_list = ft_split(path_value, ':', &content->g_collector);
	if (!path_list)
		return (NULL);
	return (path_list);
}
