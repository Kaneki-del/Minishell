/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:44:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 17:41:06 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmds_length(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	init_echo_vars(t_echo_vars *echo_vars, char **cmd, t_container *content)
{
	echo_vars->i = 1;
	echo_vars->j = 1;
	echo_vars->second_check = 0;
	echo_vars->check = 0;
	echo_vars->new_cmds = gc(sizeof(char *) * (get_cmds_length(cmd) + 1), \
	&content->g_collector, content);
	echo_vars->new_cmds[0] = cmd[0];
}

char	**remove_repeated(char **cmd, t_container *content)
{
	t_echo_vars	echo_vars;

	init_echo_vars(&echo_vars, cmd, content);
	while (cmd[echo_vars.i])
	{
		if (ft_strcmp(cmd[echo_vars.i], "-n") == 0 && echo_vars.check == 0)
		{
			if (echo_vars.second_check == 0)
				echo_vars.check = 1;
			else
				echo_vars.check = 0;
			echo_vars.new_cmds[echo_vars.j++] = cmd[echo_vars.i++];
			continue ;
		}
		else if (ft_strcmp(cmd[echo_vars.i], "-n") != 0)
		{
			echo_vars.second_check = 1;
			echo_vars.check = 0;
			echo_vars.new_cmds[echo_vars.j++] = cmd[echo_vars.i++];
		}
	}
	echo_vars.new_cmds[echo_vars.j] = NULL;
	return (echo_vars.new_cmds);
}

char	**check_echo_options(char **cmd, t_gc **g_collector, \
t_container *content)
{
	int	i;
	int	j;

	i = 1;
	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strcmp(cmd[0], "echo") != 0)
		return (cmd);
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1] != '\0')
		{
			j = 1;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] == '\0')
				cmd[i] = ft_strdup("-n", g_collector, content);
			else
				break ;
		}
		i++;
	}
	return (remove_repeated(cmd, content));
}
