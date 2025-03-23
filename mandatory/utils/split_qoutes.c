/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:48:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 23:56:42 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_inqoutes(char quote, size_t *i, int *in_quote, char *s)
{
	if (s[*i] == '\'' || s[*i] == '"')
	{
		if (!*in_quote)
			(1) && (*in_quote = 1, quote = s[*i]);
		else if (s[*i] == quote)
			(1) && (*in_quote = 0, quote = 0);
	}
	return (quote);
}

size_t	words_count(char *s, char c)
{
	size_t	count;
	int		in_quote;
	char	quote;
	size_t	i;

	count = 0;
	in_quote = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		while ((s[i] == c || s[i] == '\t') && !in_quote)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && (in_quote || (s[i] != c && s[i] != '\t')))
		{
			quote = is_inqoutes(quote, &i, &in_quote, s);
			i++;
		}
	}
	return (count);
}

static char	*store_next_word(char *s, size_t *i, char c, t_container *content)
{
	size_t	start;
	size_t	len;
	int		in_quote;
	char	quote;
	char	*word;

	len = 0;
	in_quote = 0;
	quote = 0;
	while (s[*i] == c || s[*i] == '\t')
		(*i)++;
	start = *i;
	while (s[*i] && (in_quote || (s[*i] != c && s[*i] != '\t')))
	{
		quote = is_inqoutes(quote, i, &in_quote, s);
		(*i)++;
		len++;
	}
	word = gc(len + 1, &content->g_collector, content);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start, len + 1);
	return (word);
}

char	**ft_split(char *s, char c, t_gc **g_collector, t_container *content)
{
	char	**p;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	p = gc((words_count(s, c) + 1) * sizeof(char *), g_collector, content);
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while ((words_count(s, c)) > j)
	{
		p[j] = store_next_word(s, &i, c, content);
		if (!(p[j]))
			return (NULL);
		j++;
	}
	p[j] = NULL;
	return (p);
}
