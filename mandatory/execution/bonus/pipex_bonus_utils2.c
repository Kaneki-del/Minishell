/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/12 17:44:23 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (ret == -1)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2, 's');
		ft_putstr_fd(file, 2, 'n');
	}
	return (ret);
}

void	print_error(char *cmd_input)
{
	ft_putstr_fd("zsh: command not found: ", 2, 's');
	ft_putstr_fd(cmd_input, 2, 'n');
	exit(127);
}

void	executing(char **env, char *cmd_input)
{
	char	**cmd_args;
	char	*cmd_path;

	if (!env || !cmd_input)
		exit (127);
	cmd_path = find_executable_path(env, cmd_input);
	if (!cmd_path)
		print_error(cmd_input);
	cmd_args = ft_split(cmd_input, ' ');
	if (cmd_args)
	{
		if (execve(cmd_path, cmd_args, env) == -1)
		{
			free(cmd_path);
			free_commands(cmd_args);
			print_error(cmd_args[0]);
			exit(127);
		}
	}
	free(cmd_path);
	free_commands(cmd_args);
	exit (127);
}

/* int	get_doc(char **av) */
/* { */
/* 	char	*buff; */
/* 	int		fd; */
/* 	int		av_lent; */
/**/
/* 	av_lent = ft_strlen(av[2]); */
/* 	fd = open_file("bonus/utils_bonus.c", 1); */
/* 	while (1) */
/* 	{ */
/* 		write(1, "heredoc> ", 9); */
/* 		buff = get_next_line(0); */
/* 		while (!buff) */
/* 			buff = get_next_line(0); */
/* 		if (ft_strncmp(av[2], buff, av_lent) == 0 && buff[av_lent] == '\n') */
/* 			break ; */
/* 		write(fd, buff, ft_strlen(buff)); */
/* 		free(buff); */
/* 	} */
/* 	free(buff); */
/* 	close(fd); */
/* 	fd = open_file("bonus/utils_bonus.c", 0); */
/* 	return (fd); */
/* } */
