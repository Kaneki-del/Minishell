/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expanding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:38:51 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 17:40:23 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	here_doc_expander(t_container *content, char *command, \
char **new_command, int *i)
{
	char	*curent_part;

	curent_part = NULL;
	(*i)++;
	if (command[(*i)] == '?')
	{
		(*i)++;
		*new_command = ft_strjoin(*new_command, ft_itoa(content->status, \
		content), &content->g_collector, content);
		return (1);
	}
	else if (((ft_isdigit(command[(*i)]) || (!ft_isalpha(command[(*i)]) \
	&& command[(*i)] != '_'))))
		(*i)++;
	else if (ft_isalnum(command[(*i)]) || command[(*i)] == '_')
	{
		curent_part = expand(content, command, i, 1);
		if (curent_part)
			*new_command = ft_strjoin(*new_command, curent_part, \
			&content->g_collector, content);
		return (1);
	}
	return (0);
}

char	*expand_here_doc_lines(t_container *content, char *command)
{
	int		i;
	char	*new_command;

	if (!command)
		return (NULL);
	i = 0;
	new_command = NULL;
	while (command[i])
	{
		if (command[i] == '$' && (ft_isalnum(command[i + 1]) \
		|| command[i + 1] == '?' || command[i + 1] == '_'))
		{
			if (here_doc_expander(content, command, &new_command, &i) == 1)
				continue ;
		}
		new_command = ft_strchr_join(new_command, command[i], content);
		i++;
	}
	return (new_command);
}
