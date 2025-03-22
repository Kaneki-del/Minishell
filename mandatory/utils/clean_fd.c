/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:50:11 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 17:51:01 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_fds(t_data *list)
{
	t_data	*current;

	current = list;
	while (current)
	{
		if (current->out_fd != 0)
			close(current->out_fd);
		if (current->in_fd != 0)
			close(current->in_fd);
		current = current->next;
	}
}

void	clean_exit2(t_container *content, int exit_code)
{
	clean_fds(content->data);
	clear_bin(&content->g_collector);
	clear_bin(&content->g_env_collector);
	exit(exit_code);
}

void	clean_exit(t_container *content, int exit_code)
{
	clean_fds(content->data);
	clear_bin(&content->g_collector);
	clear_bin(&content->g_env_collector);
	if (content->if_pipe != PIPE)
		write(1, "exit\n", 5);
	exit(exit_code);
}
