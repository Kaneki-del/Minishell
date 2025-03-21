/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proccess_mangement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:56:04 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/21 01:28:48 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	first_child(t_container *content, t_data *current, int *p_fd)
{
	if (get_fds(current, content) != 0)
		exit(1);
	close(p_fd[0]);
	if (current->out_fd == 0)
		current->out_fd = p_fd[1];
	else
		close(p_fd[1]);
	if (check_builtin_commands(current->cmds))
	{
		(built_in(current, content));
		exit(content->status);
	}
	if (current->in_fd != 0)
	{
		if (dup2(current->in_fd, 0) < 0)
		{
			perror("error in dup");
			exit(1);
		}
	}
	if (dup2(current->out_fd, 1) < 0)
		(perror("error in dup2"), exit(1));
	executing(current, content);
}

static void	midle_child(t_data *current, int *p_fd, t_container *content,
		int in)
{
	if (get_fds(current, content) != 0)
		exit(1);
	close(p_fd[0]);
	if (current->out_fd == 0)
		current->out_fd = p_fd[1];
	else
		close(p_fd[1]);
	if (current->in_fd == 0)
		current->in_fd = in;
	else
		close(in);
	if (check_builtin_commands(current->cmds))
	{
		(built_in(current, content));
		exit(content->status);
	}
	if (dup2(current->in_fd, 0) < 0)
	{
		perror("error in dup2");
		exit(1);
	}
	if (dup2(current->out_fd, 1) < 0)
		(perror("error in dup2"), exit(1));
	executing(current, content);
}

void	execute_first(t_data *current, int *p_fd, t_container *content)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		handle_fork_failure(content);
		return ;
	}
	if (pid == 0)
		first_child(content, current, p_fd);
	clean_fd(current);
	close(p_fd[1]);
}

void	execut(t_container *content, t_data *current, int *p_fd, int in)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close(in);
		handle_fork_failure(content);
		if (content->fork_failed == 0)
			content->fork_failed = 1;
		return ;
	}
	if (pid == 0)
		midle_child(current, p_fd, content, in);
	close(p_fd[1]);
	close(in);
}
