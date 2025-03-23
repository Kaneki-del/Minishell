/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:35:12 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/23 11:01:25 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**filter_all(char **cmds, t_gc **g_collector, t_container *content)
{
	int	i;

	i = 0;
	if (!cmds)
		return (NULL);
	while (cmds[i])
	{
		cmds[i] = remove_quotes(cmds[i], g_collector, content);
		i++;
	}
	return (cmds);
}

int	get_char_index(char *s, char c)
{
	int		i;
	int		store;
	char	qoute;
	int		is_in;

	i = 0;
	store = 0;
	is_in = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (is_in == 0)
			{
				is_in = 1;
				qoute = s[i];
			}
			else if (is_in == 1 && qoute == s[i])
				is_in = 0;
		}
		if (s[i] == c && !is_in)
			store = i;
		i++;
	}
	return (store);
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

char	*expand(t_container *content, char *command, int *i, int is_here_doc)
{
	t_env	*pair;
	char	*key;
	int		start;

	if(!content->env_list)
		return (NULL);
	pair = NULL;
	key = NULL;
	start = (*i);
	while (command[start] && (ft_isalnum(command[start]) \
	|| command[start] == '_'))
		start++;
	key = gc(start - (*i) + 1, &content->g_collector, content);
	ft_strlcpy(key, &command[(*i)], start - (*i) + 1);
	pair = check_if_there(key, &content->env_list);
	(*i) = start;
	if (pair_check_cases(content, pair, key, is_here_doc) == 1)
		return (ft_strdup("\0", &content->g_collector, content));
	content->flag = 5;
	if (!pair->value)
		return (NULL);
	return (pair->value);
}
