/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:39:16 by sait-nac          #+#    #+#             */
/*   Updated: 2025/01/10 10:55:19 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_env_path(char **env)
{
	int		i;
	char	*path_value;
	char	*env_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	env_path = env[i];
	path_value = ft_substr(env_path, 5, ft_strlen(env_path));
	return (path_value);
}

void	free_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		commands[i] = NULL;
		i++;
	}
	free(commands);
}

char	*check_cmd_path(char **path_list, char *cmd_name)
{
	int		i;
	char	*full_cmd_path;

	i = 0;
	while (path_list[i])
	{
		full_cmd_path = ft_strjoin(path_list[i], cmd_name, 's');
		if (!full_cmd_path)
		{
			free_commands(path_list);
			return (NULL);
		}
		if (access(full_cmd_path, X_OK) == 0)
		{
			free_commands(path_list);
			return (full_cmd_path);
		}
		free(full_cmd_path);
		i++;
	}
	free_commands(path_list);
	return (NULL);
}

static char	*try_direct_access(char **cmd_tabs)
{
	char	*cmd_v;

	if (access(cmd_tabs[0], X_OK) == 0)
	{
		cmd_v = ft_strdup(cmd_tabs[0]);
		free_commands(cmd_tabs);
		return (cmd_v);
	}
	return (NULL);
}

char	*find_executable_path(char **env, char *cmd_name)
{
	char	**cmd_tabs;
	char	**path_list;
	char	*path_value;
	char	*cmd_v;

	if (!cmd_name || !env)
		return (NULL);
	cmd_tabs = ft_split(cmd_name, ' ');
	if (!cmd_tabs || !cmd_tabs[0])
		return (free_commands(cmd_tabs), NULL);
	cmd_v = try_direct_access(cmd_tabs);
	if (cmd_v)
		return (cmd_v);
	path_value = get_env_path(env);
	if (!path_value)
		return (free_commands(cmd_tabs), NULL);
	path_list = ft_split(path_value, ':');
	free(path_value);
	if (!path_list)
		return (free_commands(cmd_tabs), NULL);
	cmd_v = check_cmd_path(path_list, cmd_tabs[0]);
	free_commands(cmd_tabs);
	return (cmd_v);
}
