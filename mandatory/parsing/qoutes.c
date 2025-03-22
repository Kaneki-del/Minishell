/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 03:10:10 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 03:14:09 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**filterd(char **cmds, t_gc **g_collector)
{
	int	i;

	i = 0;
	if (!cmds)
		return (NULL);
	while (cmds[i] != NULL)
	{
		if (i > 0 && ft_strncmp(cmds[i - 1], "<<", 3) != 0)
		{
			cmds[i] = remove_quotes(cmds[i], g_collector);
			if (!cmds[i])
				return (NULL);
		}
		else if (ft_strncmp(cmds[i], "''", 3) == 0 \
		|| ft_strncmp(cmds[i], "\"\"", 3) == 0)
			cmds[i] = remove_quotes(cmds[i], g_collector);
		i++;
	}
	return (cmds);
}

int	check_is_in_qoutes(char *str)
{
	if (str && (str[0] == '"' || str[0] == '\'') \
	&& (str[ft_strlen(str) - 1] == '"' || str[ft_strlen(str) - 1] == '\''))
		return (1);
	return (0);
}

char	*add_qoutations(char *command, t_gc **g_collector)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 1;
	if (check_is_in_qoutes(command))
		return (command);
	res = gc(ft_strlen(command) + 3, g_collector);
	res[0] = '"';
	while (command[i])
	{
		res[j] = command[i];
		i++;
		j++;
	}
	res[j] = '"';
	res[j + 1] = '\0';
	return (res);
}
