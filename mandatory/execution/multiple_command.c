/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:16:09 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/16 00:17:35 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_fork_failure(t_container *content)
{
	if (content->fork_failed == 0)
	{
		ft_putstr_fd("BASH: fork: Resource temporarily unavailable\n", 2);
		content->fork_failed = 1;
	}
	clean_fds(content->data);
	content->status = 1;
}

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
			perror("dup2 in_fd");
			exit(1);
		}
	}
	if (dup2(current->out_fd, 1) < 0)
		(perror("dup2 out_fd"), exit(1));
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
		perror("dup2 in_fd");
		exit(1);
	}
	if (dup2(current->out_fd, 1) < 0)
		(perror("dup2 out_fd"), exit(1));
	executing(current, content);
}

static void	execut(t_container *content, t_data *current, int *p_fd, int in)
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

static void	last_child(t_data *current, int *p_fd, t_container *content)
{
	if (get_fds(current, content) != 0)
		exit(1);
	if (current->in_fd == 0)
		current->in_fd = p_fd[0];
	else
		close(p_fd[0]);
	if (check_builtin_commands(current->cmds))
	{
		(built_in(current, content));
		exit(content->status);
	}
	if (current->in_fd != 0)
	{
		if (dup2(current->in_fd, 0) < 0)
		{
			perror("dup2 in_fd");
			exit(1);
		}
	}
	if (current->out_fd != 0)
	{
		if (dup2(current->out_fd, 1) < 0)
			(perror("dup2 out_fd"), exit(1));
	}
	executing(current, content);
}

int	execute_last(t_container *content, t_data *current, int *p_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		handle_fork_failure(content);
		return (1);
	}
	if (pid == 0)
		last_child(current, p_fd, content);
	close(p_fd[0]);
	return (pid);
}

static int	handle_pipes(t_container *content)
{
	int		p_fd[2];
	t_data	*current;
	int		t;

	current = content->data;
	if (pipe(p_fd) == -1)
		exit(1);
	execute_first(current, p_fd, content);
	current = current->next;
	while (current != NULL && current->next != NULL)
	{
		t = p_fd[0];
		if (pipe(p_fd) == -1)
			exit(1);
		execut(content, current, p_fd, t);
		close(t);
		current = current->next;
		close(p_fd[1]);
	}
	return (execute_last(content, current, p_fd));
}

void	run_multiple(t_container *content)
{
	int	status;
	int	exit_code;
	int	id_last_command;

	content->fork_failed = 0;
	status = 0;
	exit_code = 0;
	id_last_command = handle_pipes(content);
	waitpid(id_last_command, &content->status, 0);
	if (content->status != 1)
		update_status(content);
	while (wait(NULL) > 0)
		;
}
