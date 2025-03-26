/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:43:40 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/26 17:15:54 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen_2d(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	in_quotations(char *command, int *i, char quote, int *is_in)
{
	if (command[(*i)] == '\'' || command[(*i)] == '"')
	{
		if (!*is_in)
		{
			*is_in = 1;
			quote = command[(*i)];
		}
		else if (*is_in && command[(*i)] == quote)
		{
			*is_in = 0;
			quote = '\0';
		}
	}
	return (quote);
}

char	*remove_quotes(char *command, t_gc **g_collector, t_container *content)
{
	char	*res;
	int		i;
	int		j;
	char	current_quote;

	current_quote = '\0';
	j = 0;
	i = 0;
	if (!command)
		return (NULL);
	res = gc(ft_strlen(command) + 1, g_collector, content);
	while (command[i])
	{
		if (current_quote == '\0' && (command[i] == '\'' || command[i] == '"'))
			current_quote = command[i++];
		else if (current_quote && command[i] == current_quote)
		{
			current_quote = '\0';
			i++;
		}
		else
			res[j++] = command[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*add_qoutations(char *command, char qoute, t_container *content)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 1;
	res = gc(ft_strlen(command) + 3, &content->g_collector, content);
	res[0] = qoute;
	while (command[i])
	{
		res[j] = command[i];
		i++;
		j++;
	}
	res[j] = qoute;
	res[j + 1] = '\0';
	return (res);
}

int	is_in_quotes(char *command, int pos)
{
	int		i;
	char	quote;
	int		is_in;

	quote = '\0';
	is_in = 0;
	i = 0;
	while (i < pos)
	{
		quote = in_quotations(command, &i, quote, &is_in);
		i++;
	}
	return (is_in);
}
