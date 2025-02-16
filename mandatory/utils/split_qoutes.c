/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:48:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/13 11:35:29 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	words_count(const char *s, char c)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = -1;
	count = 0;
	quote = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			count++;
			quote = s[i];
			while (s[++i] && s[i] != quote)
				;
			if (s[i] == quote)
				i++;
			quote = 0;
		}
		else if (s[i] != c && (i == 0 || s[i - 1] == c) && !quote)
			count++;
	}
	return (count);
}

static void	mem_free(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static char	*fill(char *p, const char *s, size_t i, size_t len_chrs)
{
	size_t	k;

	k = 0;
	while (k < len_chrs)
	{
		p[k] = s[i + k];
		k++;
	}
	p[k] = '\0';
	return (p);
}

static char	*store_next_word(const char *s, size_t *i, char c)
{
	char	*p;
	size_t	char_count;
	char	q;

	char_count = 0;
	q = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (s[*i] == '\'' || s[*i] == '"' )
	{
		q = s[*i];
		char_count++;
		while (s[*i + char_count] && s[*i + char_count] != q)
			char_count++;
		if (s[*i + char_count] == q)
			char_count++;
	}
	while (s[*i + char_count] && s[*i + char_count] != c) // "this is na"this
		char_count++;
	p = (char *)malloc(char_count + 1);
	if (!p)
		return (NULL);
	fill(p, s, *i, char_count);
	*i += char_count;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	p = malloc((words_count(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while ((words_count(s, c)) > j)
	{
		p[j] = store_next_word(s, &i, c);
		if (!(p[j]))
		{
			mem_free(p);
			return (NULL);
		}
		j++;
	}
	p[j] = NULL;
	return (p);
}