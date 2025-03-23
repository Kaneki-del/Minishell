/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:55:30 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/23 11:00:45 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*check_if_there(const char *key, t_env **env_list)
{
	t_env	*temp;

	temp = NULL;
	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
