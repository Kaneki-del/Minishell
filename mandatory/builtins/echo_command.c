/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:53:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 23:17:04 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_echo(t_container *content, t_data *current, char **cmd)
{
	char	*old_cmd;
	int		i;

	old_cmd = ft_strdup(current->befor_expanding, &content->g_collector, \
	content);
	if (!old_cmd)
		return (NULL);
	content->status = content->is_status;
	expanding_cmds_redirections(content, &current->befor_expanding, NULL, 0);
	content->status = 0;
	cmd = ft_split(current->befor_expanding, ' ', &content->g_collector, \
	content);
	if (!cmd || !cmd[0])
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(old_cmd, '"') || ft_strchr(old_cmd, '\''))
			cmd[i] = remove_quotes(cmd[i], &content->g_collector, content);
		i++;
	}
	return (cmd);
}

static void	echo(t_container *content, t_data *current)
{
	int		i;
	int		new_line;
	int		espace;
	char	**cmd;

	espace = 0;
	new_line = 0;
	cmd = NULL;
	cmd = expand_echo(content, current, cmd);
	cmd = check_echo_options(cmd, &content->g_collector, content);
	i = 1;
	if (ft_strcmp(cmd[i], "-n") == 0)
	{
		i++;
		new_line = 1;
	}
	while (cmd[i])
	{
		if (espace == 1)
			write(1, " ", 1);
		ft_putstr_fd(cmd[i++], 1);
		espace = 1;
	}
	if (new_line == 0)
		write(1, "\n", 1);
}

void	handle_echo(t_container *content, t_data *current)
{
	int		i;
	int		saved_stdout;
	char	**cmd;

	cmd = current->cmds;
	saved_stdout = rideraction_builtins(current, content);
	i = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
		echo(content, current);
	else
		write(1, "\n", 1);
	if (saved_stdout != -1)
	{
		if (dup2(saved_stdout, 1) == -1)
		{
			perror("error in dup2");
			clean_exit2(content, 1);
		}
		close(saved_stdout);
	}
}
