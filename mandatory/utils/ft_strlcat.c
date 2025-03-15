/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:09:29 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/15 23:09:45 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_lent;
	size_t	src_lent;
	size_t	i;

	i = 0;
	src_lent = ft_strlen(src);
	if (dstsize == 0)
		return (src_lent);
	dst_lent = ft_strlen(dst);
	if (dst_lent >= dstsize)
		return (dstsize + src_lent);
	while (i < (dstsize - dst_lent - 1) && src[i])
	{
		dst[dst_lent + i] = src[i];
		i++;
	}
	dst[dst_lent + i] = '\0';
	return (dst_lent + src_lent);
}
