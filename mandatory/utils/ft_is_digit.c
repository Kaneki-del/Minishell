/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:32:45 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 21:35:11 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str_char;

	i = 0;
	str_char = (unsigned char *)b;
	while (i < len)
		str_char[i++] = (unsigned char)c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*ptr;

	total_size = count * size;
	if (size != 0 && total_size / size != count)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
