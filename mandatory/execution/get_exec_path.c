/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:39:16 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/16 14:50:41 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_cmd_path(char **path_list, char *cmd_name, t_gc **gc)
{
	int		i;
	char	*full_cmd_path;

	i = 0;
	while (path_list[i])
	{
		full_cmd_path = ft_strjoin(path_list[i], "/", gc);
		full_cmd_path = ft_strjoin(full_cmd_path, cmd_name, gc);
		if (!full_cmd_path)
			return (NULL);
		if (access(full_cmd_path, X_OK) == 0)
			return (full_cmd_path);
		i++;
	}
	return (NULL);
}

static void	print_dir_error(t_data *current)
{
	if (ft_strcmp(current->cmds[0], ".") == 0 || ft_strcmp(current->cmds[0],
			"..") == 0)
	{
		if (!ft_strcmp(current->cmds[0], ".."))
		{
			ft_error_exec_two("mshell: ",
				current->cmds[0], ": command not found", 2);
			exit(127);
		}
		else
		{
			ft_putstr_fd("mshell: .: filename argument required\n", 2);
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
			exit(2);
		}
	}
}

static char	*try_direct_access(t_data *current, t_container *content)
{
	char	*cmd_v;

	if (access(current->cmds[0], F_OK) == 0)
	{
		if (access(current->cmds[0], X_OK) == 0)
		{
			cmd_v = ft_strdup(current->cmds[0], &content->g_collector);
			return (cmd_v);
		}
		else
		{
			ft_error_exec_two("mshell: ", current->cmds[0],
				": Permission denied", 2);
			exit(126);
		}
	}
	return (NULL);
}

static char	*executable(t_data *current, t_container *content)
{
	char	*cmd_v;

	cmd_v = try_direct_access(current, content);
	if (!cmd_v)
	{
		ft_error_exec_two("mshell: ", current->cmds[0],
			": No such file or directory", 2);
		exit(127);
	}
	return (cmd_v);
}

char	*find_executable_path(t_data *current, t_container *content)
{
	char	*cmd_v;
	char	**path;

	path = NULL;
	if (ft_strchr(current->cmds[0], '/') != NULL)
		cmd_v = executable(current, content);
	else
		path = get_path(content);
	if (!path || !path[0])
	{
		if (access(current->cmds[0], X_OK) == 0)
		{
			cmd_v = ft_strdup(current->cmds[0], &content->g_collector);
			return (cmd_v);
		}
		else
		{
			ft_error_exec_two("mshell: ", current->cmds[0],
				": No such file or directory", 2);
			exit(127);
		}
	}
	print_dir_error(current);
	cmd_v = check_cmd_path(path, current->cmds[0], &content->g_collector);
	return (cmd_v);
}
