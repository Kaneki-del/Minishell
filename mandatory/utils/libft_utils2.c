/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:42:48 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 21:42:54 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

static size_t	digit_len(long dig)
{
	size_t	i;

	i = 0;
	if (dig <= 0)
	{
		dig = -dig;
		i = 1;
	}
	while (dig > 0)
	{
		dig /= 10;
		i++;
	}
	return (i);
}

static char	*store(char *p, long num, size_t digitCount)
{
	while (num > 0)
	{
		p[--digitCount] = (num % 10) + '0';
		num /= 10;
	}
	return (p);
}

char	*ft_itoa(int n, t_container *content)
{
	size_t	len_digit;
	char	*p;
	long	num;

	num = n;
	len_digit = digit_len(num);
	p = gc(len_digit + 1, &content->g_collector, content);
	if (!p)
		return (NULL);
	p[len_digit] = '\0';
	if (num <= 0)
	{
		if (num == 0)
		{
			p[0] = '0';
			return (p);
		}
		num = -num;
		p[0] = '-';
	}
	store(p, num, len_digit);
	return (p);
}
