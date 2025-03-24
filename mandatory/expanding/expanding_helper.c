/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:35:12 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/24 23:06:50 by kben-tou         ###   ########.fr       */
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

char *add_quotes(char *str, t_container *content)
{
    if (str == NULL) {
        return NULL;
    }

    // Allocate memory for the new string with quotes
    size_t len = ft_atoi(str);
    char *quoted_str = gc(len + 3, &content->g_collector, content); // 2 quotes + 1 null terminator

    if (quoted_str == NULL) {
        return NULL;
    }

    // Add the quotes and copy the original string
    quoted_str[0] = '"';
    ft_strlcpy(quoted_str + 1, str, len + 1);
    quoted_str[len + 1] = '"';
    quoted_str[len + 2] = '\0';

    return quoted_str;
}

char *ft_strtrim(char *s1, char *set, t_container *content) {
    size_t s;
    size_t e;
    size_t i;
    char *res;

    s = 0;
    e = 0;
    i = 0;
    if (!s1)
        return (NULL);
    if (!set)
        return (ft_strdup(s1, &content->g_collector, content));
    while (s1[s] && ft_strchr(set, s1[s]))
        s++;
    e = ft_strlen(s1);
    while (e > s && ft_strchr(set, s1[e - 1]))
        e--;
    res = (char *)malloc((e - s) + 1);
    if (!res)
        return (NULL);
    while (s < e)
        res[i++] = s1[s++];
    res[i] = '\0';
    return (res);
}

char	*expand(t_container *content, char *command, int *i, int is_here_doc)
{
	t_env	*pair;
	char	*key;
	int		start;

	if (!content->env_list)
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
	if (content->shoud_skeep == 2)
		pair->value = add_quotes(pair->value, content);
	return (pair->value);
}