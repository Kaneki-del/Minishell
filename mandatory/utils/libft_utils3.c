/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:43:40 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 21:45:24 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen_2d(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	in_quotations(char *command, int *i, char quote, int *is_in)
{
	if (command[(*i)] == '\'' || command[(*i)] == '"')
	{
		if (!*is_in)
		{
			*is_in = 1;
			quote = command[(*i)];
		}
		else if (*is_in && command[(*i)] == quote)
		{
			*is_in = 0;
			quote = '\0';
		}
	}
	return (quote);
}
