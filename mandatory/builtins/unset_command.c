/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:03:31 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/21 01:16:55 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	filter_unset(char *key)
{
	int	i;

	i = 0;
	if ((key[0] >= '0' && key[0] <= '9') || key[0] == '\0')
		return (1);
	while (key[i] && key[i])
	{
		if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A'
					&& key[i] <= 'Z') || (key[i] >= '0' && key[i] <= '9')
				|| key[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

static void	unset_key(char **cmd, t_container *content)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = NULL;
	while (cmd[i])
	{
		if (filter_unset(cmd[i]) == 0)
		{
			temp = check_if_there(cmd[i], &content->env_list);
			if (temp != NULL && temp->print_flag == 0)
				delete_node(&content->env_list, temp->key);
		}
		else
		{
			ft_error_exec("mshell: unset:", cmd[i],
				": not a valid identifier", 2);
			content->status = 1;
		}
		i++;
	}
}

void	handle_unset(char **cmd, t_container *content, t_data *current)
{
	int	i;

	clean_fd(current);
	i = 0;
	content->status = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
		unset_key(cmd + 1, content);
}
