/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/14 21:36:11 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* int	open_file(char *file, int in_or_out) */
/* { */
/* 	int	ret; */
/**/
/* 	if (in_or_out == 0) */
/* 		ret = open(file, O_RDONLY, 0777); */
/* 	if (in_or_out == 1) */
/* 		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777); */
/* 	if (in_or_out == 2) */
/* 		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777); */
/* 	if (ret == -1) */
/* 	{ */
/* 		ft_putstr_fd("zsh: no such file or directory: ", 2, 's'); */
/* 		ft_putstr_fd(file, 2, 'n'); */
/* 	} */
/* 	return (ret); */
/* } */

void	print_error(char *cmd_input)
{
	ft_putstr_fd("zsh: command not found: ", 2, 's');
	ft_putstr_fd(cmd_input, 2, 'n');
	exit(127);
}

void	executing(char **env, char **cmd_args)
{
	char	*cmd_path;

	if (!env)
		exit (127);
	cmd_path = find_executable_path(env, cmd_args);
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

