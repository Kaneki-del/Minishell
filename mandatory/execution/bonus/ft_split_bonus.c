/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:41:35 by sait-nac          #+#    #+#             */
/*   Updated: 2025/01/10 09:20:15 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	*free_arr(char **str, size_t lent)
{
	size_t	i;

	i = 0;
	while (i < lent)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	word_lent(const char *w, char c)
{
	size_t	i;

	i = 0;
	while (w[i] && (w[i] != c))
		i++;
	return (i);
}

static int	cownt_words(const char *str, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while ((str[i] == c) && str[i])
			i++;
		if (str[i] != '\0')
			count++;
		while ((str[i] != c) && str[i])
			i++;
	}
	return (count);
}

static char	*append(const char *str, char c)
{
	size_t	lent;
	size_t	i;
	char	*ptr;

	i = 0;
	lent = word_lent(str, c);
	ptr = (char *)malloc(sizeof(char) * (lent + 1));
	if (!ptr)
		return (NULL);
	while (i < lent)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (cownt_words(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (*s != '\0')
	{
		while (*s && (*s == c))
			s++;
		if (*s != '\0')
		{
			str[i] = append(s, c);
			if (str[i] == NULL)
				return (free_arr(str, i));
			i++;
		}
		while (*s && (*s != c))
			s++;
	}
	str[i] = 0;
	return (str);
}
