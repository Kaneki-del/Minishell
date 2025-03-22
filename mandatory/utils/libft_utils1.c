/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:35:48 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 15:24:42 by kben-tou         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len, t_container *content)
{
	size_t	s_len;
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup("", &content->g_collector, content));
	if (start + len > s_len)
		len = s_len - start;
	sub = gc(len + 1, &content->g_collector, content);
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

char *ft_chrjoin(char c, char b, t_container *content)
{
	char *new;

	new = gc(3, &content->g_collector, content);
	if (!new)
		return (NULL);
	new[0] = c;
	new[1] = b;
	new[2] = '\0';
	return (new);
}

char *ft_strchr_join(char *s1, char c, t_container *content)
{
	size_t	total_len;
	char	*result;

	if (!s1)
	{
		result = gc(2, &content->g_collector, content);
		if (!result)
			return (NULL);
		result[0] = c;
		result[1] = '\0';
		return (result);
	}
	total_len = ft_strlen(s1) + 2;
	result = gc(total_len, &content->g_collector, content);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len);
	result[ft_strlen(s1)] = c;
	result[ft_strlen(s1) + 1] = '\0';
	return (result);
}
