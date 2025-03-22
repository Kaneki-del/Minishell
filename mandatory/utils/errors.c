/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:54:52 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 17:55:27 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *msg, char *dis, int fd)
{
	if (!msg)
		return ;
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(" `", fd);
	ft_putstr_fd(dis, fd);
	ft_putstr_fd("'\n", fd);
}

void	ft_error_exec(char *msg, char *dis, char *left, int fd)
{
	if (!msg)
		return ;
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(" `", fd);
	ft_putstr_fd(dis, fd);
	ft_putstr_fd("'", fd);
	ft_putstr_fd(left, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_error_exec_two(char *msg, char *dis, char *left, int fd)
{
	if (!msg)
		return ;
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(dis, fd);
	ft_putstr_fd(left, fd);
	ft_putstr_fd("\n", fd);
}
