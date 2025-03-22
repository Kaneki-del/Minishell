/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 02:17:56 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	exec_error(t_data *current, char *cmd_path)
{
	if (is_directory(cmd_path))
	{
		ft_error_exec_two("mshell: ", current->cmds[0], ": is a directory", 2);
		exit(126);
	}
	if (access(current->cmds[0], X_OK) == 0)
		exit(0);
}

void    executing(t_data *current, t_container *content)
{
	char	*cmd_path;
	char	**list_char;

    if (!content->env_list)
        exit(0);
    if (!current->cmds || !current->cmds[0])
        exit(0);
    if (content->flag == 5 && (ft_strchr(current->befor_expanding, '\'') || ft_strchr(current->befor_expanding, '"')))
        current->cmds = filter_all(current->cmds, &content->g_collector);
    cmd_path = find_executable_path(current, content);
    if (!cmd_path || ft_strcmp(current->cmds[0], "\0") == 0)
    {
        ft_error_exec_two("mshell: ", current->cmds[0],
            ": command not found", 2);
        clear_bin(&content->g_collector);
        clear_bin(&content->g_env_collector);
        exit(127);
    }
    list_char = env_to_array(content);
    if (current->cmds)
    {
        if (execve(cmd_path, current->cmds, list_char) == -1)
            exec_error(current, cmd_path);
    }
}
