/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:53:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/18 23:43:52 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo(char **cmd)
{
	int	i;
	int	new_line;
	int	espace;

	espace = 0;
	new_line = 0;
	i = 0;
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

void	handle_echo(t_data *list)
{
	int		i;
	int		saved_stdout;
	char	**cmd;
	
	
	cmd = list->cmds;
	saved_stdout = rideraction_builtins(list);
	
	i = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
		echo(cmd + 1);
	else
		write(1, "\n", 1);
	if (saved_stdout != -1)
	{
		if (dup2(saved_stdout, 1) == -1)
		{
			perror("error in dup2");
			exit(1);
		}
		close(saved_stdout);
	}
}
