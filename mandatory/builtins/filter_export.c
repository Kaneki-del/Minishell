/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:01:31 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 15:05:30 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	filter_key(char *key, char *value)
{
	int	i;

	i = 0;
	if (key[0] >= '0' && key[0] <= '9')
		return (1);
	while (key[i] && key[i + 1])
	{
		if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A'
					&& key[i] <= 'Z') || (key[i] >= '0' && key[i] <= '9')
				|| key[i] == '_'))
			return (1);
		i++;
	}
	if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] >= '0' && key[i] <= '9') || key[i] == '_'
			|| (key[i] == '+' && value != NULL)))
	{
		return (1);
	}
	return (0);
}

void	do_mode(char **key_value, t_env **node, t_container *content, int a)
{
	char	*value;

	value = NULL;
	value = key_value[1];
	if (a == 1)
		(*node)->value = ft_strjoin((*node)->value, value,
				&content->g_env_collector, content);
	else
	{
		if (value)
			(*node)->value = ft_strdup(value, &content->g_env_collector,
					content);
	}
}

char	**get_befor(const char *cmd, t_container *content)
{
	int		i;
	char	**to_return ;

	i = 0;
	to_return = (char **)gc(sizeof(char *) * 3, &content->g_collector, content);
	while (cmd[i] != '=' && cmd[i])
		i++;
	to_return[0] = ft_substr(cmd, 0, i, content);
	if (cmd[i] == '=')
	{
		i++;
		to_return[1] = ft_substr(cmd, i, ft_strlen(cmd + i),
				content);
	}
	else
		to_return[1] = NULL;
	to_return[2] = 0;
	return (to_return);
}

void	valid_key(char **key_value, t_container *content)
{
	int		a;
	t_env	*temp;

	a = 0;
	if (key_value[0][ft_strlen(key_value[0]) - 1] == '+')
	{
		key_value[0][ft_strlen(key_value[0]) - 1] = '\0';
		a = 1;
	}
	temp = check_if_there(key_value[0], &content->env_list);
	if (key_value[0] && ft_strcmp(key_value[0], "_"))
	{
		if (temp != NULL)
			do_mode(key_value, &temp, content, a);
		else
			lstadd_back_env(&content->env_list, lstnew_env(key_value[0],
					key_value[1], content, 0));
	}
}

void	add_export(char **cmd, t_container *content)
{
	int		i;
	char	**splited_equal;

	i = 0;
	clean_fd(content->data);
	while (cmd[i])
	{
		splited_equal = get_befor(cmd[i], content);
		if (filter_key(splited_equal[0], splited_equal[1]) == 0
			&& splited_equal[0])
			valid_key(splited_equal, content);
		else
		{
			ft_error_exec("mshell: export:", cmd[i], ": not a valid identifier",
				2);
			content->status = 1;
		}
		i++;
	}
}
