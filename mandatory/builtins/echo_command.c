/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:53:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 02:16:09 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo(t_container *content, t_data *current)
{
	int	i;
	int	new_line;
	int	espace;
	char **cmd;
	char *old_cmd;
	int j;

	espace = 0;
	new_line = 0;
	cmd = NULL;
	old_cmd = ft_strdup(current->befor_expanding, &content->g_collector);
	if (!old_cmd)
		return ;
	content->status = content->is_status;
	expanding_cmds_redirections(content, &current->befor_expanding, NULL, 0);
	content->status = 0;
	cmd = ft_split(current->befor_expanding, ' ', &content->g_collector);
	if (!cmd || !cmd[0])
		return ;
	j = 0;
	while (cmd[j])
	{
		if (ft_strchr(old_cmd, '"') || ft_strchr(old_cmd, '\''))
			cmd[j] = remove_quotes(cmd[j], &content->g_collector);
		j++;
	}
	cmd = check_echo_options(cmd, &content->g_collector);
	if (!cmd || !cmd[0])
		return ;
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
		ft_putstr_fd(cmd[i], 1);
		espace = 1;
		i++;
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
