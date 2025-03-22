/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ridirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:22:24 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/21 01:37:29 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_file_part_two(char *file, int in_or_out)
{
	int	ret;

	ret = 0;
	if (in_or_out == 1)
	{
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (is_directory(file))
			return (ft_error_exec_two("mshell: ", file,
					": Is a directory", 2), -1);
		if (ret == -1)
			return (ft_error_exec_two("mshell: ", file,
					": Permission denied", 2), -1);
	}
	else if (in_or_out == 2)
	{
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (is_directory(file))
			return (ft_error_exec_two("mshell: ", file,
					": Is a directory", 2), -1);
		if (ret == -1)
			return (ft_error_exec_two("mshell: ", file,
					": Permission denied", 2), -1);
	}
	return (ret);
}

static int	open_file(char *file, int in_or_out)
{
	int	ret;

	ret = 0;
	if (!file || file[0] == '\0')
	{
		ft_error_exec_two("mshell: ", file, ": No such file or directory", 2);
		return (-1);
	}
	if (in_or_out == 0)
	{
		ret = open(file, O_RDONLY, 0644);
		if (ret == -1)
		{
			if (access(file, F_OK) == -1)
				ft_error_exec_two("mshell: ", file,
					": No such file or directory", 2);
			else if (access(file, R_OK) == -1)
				ft_error_exec_two("mshell: ", file, ": Permission denied", 2);
		}
	}
	else
		ret = open_file_part_two(file, in_or_out);
	return (ret);
}

static int	rediractions_out(t_data *list, int fd, int *i)
{
	(*i)++;
	if (list->out_fd != 0)
		close(list->out_fd);
	list->out_fd = open_file(list->directions[*i], fd);
	if (list->out_fd == -1)
		return (1);
	return (0);
}

static int	rideractions_handler(t_data *list, int *i)
{
	if (ft_strcmp(list->directions[*i], ">") == 0)
	{
		if (rediractions_out(list, 1, i) == 1)
			return (1);
	}
	else if (ft_strcmp(list->directions[*i], "<") == 0)
	{
		(*i)++;
		if (list->in_fd != 0)
			close(list->in_fd);
		list->in_fd = open_file(list->directions[*i], 0);
		if (list->in_fd == -1)
			return (1);
	}
	else if (ft_strcmp(list->directions[*i], ">>") == 0)
	{
		if (rediractions_out(list, 2, i) == 1)
			return (1);
	}
	return (0);
}

int	get_fds(t_data *list, t_container *content)
{
	char	**full_cmd;
	int		i;

	(void)content;
	full_cmd = list->directions;
	i = 0;
	if (!full_cmd || !full_cmd[0])
		return (0);
	while (full_cmd[i])
	{
		if (rideractions_handler(list, &i) == 1)
			return (1);
		i++;
	}
	return (0);
}
