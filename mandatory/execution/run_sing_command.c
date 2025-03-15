/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sing_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:39:04 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/15 23:39:05 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	chidl_single(t_data *current, t_container *content)
{
	if (current->in_fd != 0)
	{
		if (dup2(current->in_fd, 0) < 0)
		{
			close(current->in_fd);
			close(current->out_fd);
			exit(1);
		}
		close(current->in_fd);
	}
	if (current->out_fd != 0)
	{
		if (dup2(current->out_fd, 1) < 0)
		{
			close(current->out_fd);
			exit(1);
		}
		close(current->out_fd);
	}
	executing(current, content);
}

void	single_command(t_container *content)
{
	t_data	*current;

	current = content->data;
	if (!current->cmds || !current->cmds[0])
	{
		content->status = 0;
		return ;
	}
	if (check_builtin_commands(current->cmds))
	{
		built_in(current, content);
		return ;
	}
	content->pid = fork();
	if (content->pid < 0)
	{
		clean_fd(current);
		content->status = 1;
	}
	if (content->pid == 0)
		chidl_single(current, content);
	else
		clean_fd(current);
	waitpid(content->pid, &content->status, 0);
	update_status(content);
}
