/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:39:16 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/24 23:27:22 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_cmd_path(char **path_list, char *cmd_name,
	t_container *content)
{
	int		i;
	char	*full_cmd_path;
	
	if (!path_list || !path_list[0])
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		full_cmd_path = ft_strjoin(path_list[i], "/", &content->g_collector,
				content);
		full_cmd_path = ft_strjoin(full_cmd_path, cmd_name,
				&content->g_collector, content);
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
		ft_error_exec_two("mshell: ",
			current->cmds[0], ": command not found", 2);
		exit(127);
	}
}

static char	*try_direct_access(t_data *current, t_container *content)
{
	char	*cmd_v;

	if (access(current->cmds[0], F_OK) == 0)
	{
		if (access(current->cmds[0], X_OK) == 0)
		{
			cmd_v = ft_strdup(current->cmds[0], &content->g_collector, content);
			return (cmd_v);
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
	else if (content->env_list)
		path = get_path(content);
	if (!path || !path[0])
	{
		if (access(current->cmds[0], X_OK) == 0)
		{
			cmd_v = ft_strdup(current->cmds[0], &content->g_collector, content);
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
	cmd_v = check_cmd_path(path, current->cmds[0], content);
	return (cmd_v);
}
