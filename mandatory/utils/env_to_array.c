/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:11:48 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/15 23:12:28 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_env(t_container *content)
{
	t_env	*temp;
	int count;
	
	count = 0;
	temp = NULL;
	temp = content->env_list;
	if (!temp)
		return count;
	else
	{
		while (temp)
		{
			count++;
			temp = temp->next;
		}
	}
	return count;
}
static char **fill_env_arr(int count, t_container *content)
{
	char	**env_array;
	char	*tem;
	int		i;
	t_env	*temp;

	env_array = gc((count + 1) * sizeof(char *), &content->g_collector);
	if (!env_array)
	{
		perror("malloc failed");
		exit(1);
	}
	temp = content->env_list;
	tem = NULL;
	i = 0;
	while (temp)
	{
		tem = ft_strjoin(temp->key, "=", &content->g_collector);
		env_array[i] = ft_strjoin(tem, temp->value, &content->g_collector);
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL;
	return env_array;
}

char	**env_to_array(t_container *content)
{
	
	int		count;
	char	**env_array;
	
	count = count_env(content);
	if (count == 0)
		return NULL;
	env_array = fill_env_arr(count, content);
	return (env_array);
}