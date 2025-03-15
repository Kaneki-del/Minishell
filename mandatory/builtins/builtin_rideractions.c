/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_rideractions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:42:59 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/15 22:43:27 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	rideraction_builtins(t_data *current)
{
	int	saved_stdout;

	saved_stdout = -1;
	if (current->in_fd != 0)
		close(current->in_fd);
	if (current->out_fd != 0)
	{
		saved_stdout = dup(1);
		if (saved_stdout < 0)
		{
			perror("error saving stdout");
			exit(10);
		}
		if (dup2(current->out_fd, 1) < 0)
		{
			perror("error in dup2");
			exit(10);
		}
		close(current->out_fd);
	}
	return (saved_stdout);
}

void	clean_fd(t_data *list)
{
	if (list->in_fd != 0)
		close(list->in_fd);
	if (list->out_fd != 0)
		close(list->out_fd);
}
