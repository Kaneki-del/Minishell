/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:56:11 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 17:56:12 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	status_check(unsigned long long n,
		size_t i, char *str, t_data *current, t_container *content)
{
	if (n > LLONG_MAX / 10
		|| (n == LLONG_MAX / 10 && str[i] - '0' > LLONG_MAX % 10))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("starshell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_fds(current);
        clear_bin(&content->g_collector);
        clear_bin(&content->g_env_collector);
		exit(255);
	}
}
int ft_atoi( char *str, t_data *current, t_container *content)
{
	unsigned long long	result;
	int		signe;
	int 	i;

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
		status_check(result, i, str, current, content);
		result = (result * 10) + str[i++] - '0';
	}
	return ((result * signe));
}
