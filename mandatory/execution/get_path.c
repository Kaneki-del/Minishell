/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:52:05 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 15:07:37 by kben-tou         ###   ########.fr       */
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
				env_path = ft_strdup(current->value, &content->g_collector,
						content);
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
	path_list = ft_split(path_value, ':', &content->g_collector, content);
	if (!path_list)
		return (NULL);
	return (path_list);
}
