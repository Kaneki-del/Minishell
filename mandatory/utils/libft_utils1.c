/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:35:48 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/16 11:16:53 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	char	conv_char;
	char	*store;

	conv_char = (char)c;
	store = NULL;
	while (*s)
	{
		if (*s == conv_char)
			store = (char *)s;
		s++;
	}
	if (conv_char == '\0')
		return ((char *)s);
	return (store);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	str_len;
	size_t	i;

	i = 0;
	str_len = ft_strlen(src);
	if (dstsize == 0)
		return (str_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (str_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char *ft_chrjoin(char c, char b)
{
	char *new;

	new = malloc(3 * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = c;
	new[1] = b;
	new[2] = '\0';
	return (new);
}