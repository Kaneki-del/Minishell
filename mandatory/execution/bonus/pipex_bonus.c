/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:41:49 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/12 18:24:51 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	execut(int in_fd, int *p_fd, char **env, char *comands)
{
	pid_t	pid;
	int out_fd = p_fd[1];
	pid = fork();
	if (pid < 0)
	{
		exit(0);
	}
	if (pid == 0)
	{
		close(p_fd[0]);
		if (dup2(in_fd, 0) < 0)
		{
			close(in_fd);
			close(out_fd);
			exit(1);
		}
		if (dup2(out_fd, 1) < 0)
		{
			close(in_fd);
			close(out_fd);
			exit(1);
		}
		return (executing(env, comands), 1);

	}
	else
	{
		close(in_fd);
    close(out_fd);
    return pid; 
  }
}

/* static void	init_here_doc(int argc, char **argv, int *fd, int *i) */
/* { */
/* 	if (argc < 6) */
/* 		exit(0); */
/* 	*i = 2; */
/* 	fd[0] = get_doc(argv); */
/* 	if (fd[0] < 0) */
/* 		exit(1); */
/* 	fd[1] = open_file(argv[argc - 1], 2); */
/* } */

static void	init_files(int argc, char **argv, int *fd, int *i)
{
	*i = 1;
	fd[0] = open_file(argv[1], 0);
	fd[1] = open_file(argv[argc - 1], 1);
}

static int	handle_pipes(int *fd, char **env, char **argv, int argc)
{
	int	p_fd[2];
	int	fd_in;
	int	i;
	fd_in = fd[0];
	i = fd[2];
	while (++i < argc - 2)
	{
		if (pipe(p_fd) == -1)
			exit(1);
		execut(fd_in, p_fd, env, argv[i]);
		close(p_fd[1]);
		close(fd_in);
		fd_in = p_fd[0];
	}
	return execut(p_fd[0], fd, env, argv[argc - 2]);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[3];
	int	i;
	int status;
	status = 0;
  int exit_code;
	init_files(argc, argv, fd, &i);
	fd[2] = i;
	int id_last_command  = handle_pipes(fd, env, argv, argc);
	waitpid(id_last_command, &status, 0);
	if (WIFEXITED(status)) {
    exit_code = WEXITSTATUS(status);
    /* printf("Child process exited normally with status: %d\n", exit_code); */
  }
	while (wait(NULL) > 0)
		;
	close(fd[0]);
	close(fd[1]);
	return (exit_code);
}
