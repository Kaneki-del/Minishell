/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:56:11 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/23 00:15:43 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	status_check(unsigned long long n,
		size_t i, char *str, t_data *current)
{
	if (n > LLONG_MAX / 10
		|| (n == LLONG_MAX / 10 && str[i] - '0' > LLONG_MAX % 10))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("starshell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_fds(current);
		return (0);
	}
	return (1);
}

int	ft_atoi( char *str, t_data *current, t_container *content)
{
	unsigned long long	result;
	int					signe;
	int					i;

	i = 0;
	result = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (status_check(result, i, str, current) == 0)
			clean_exit2(content, 255);
		result = (result * 10) + str[i++] - '0';
	}
	return ((result * signe));
}
