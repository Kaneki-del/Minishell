/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:53:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/20 03:17:29 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char **expand_and_filter(char **cmds, t_container *content)
// {
// 	int i;
// 	char **cmd_no_cotes;
// 	char *hold;
// 	int j;
// 	i = 1;
// 	hold = NULL;
// 	while (cmds[i])
// 	{
// 		// cmds[i] = remove_quotes(cmds[i], &content->g_collector);
// 		j = 0;
// 		cmd_no_cotes = ft_split(cmds[i], '"', &content->g_collector);
// 		while (cmd_no_cotes[j])
// 		{
			
// 			expanding_cmds_redirections(content, &cmd_no_cotes[j], NULL);
// 			if ((content->flag != 5))
// 				cmd_no_cotes[j] = remove_quotes(cmd_no_cotes[j], &content->g_collector);	
// 			hold = ft_strjoin(hold, cmd_no_cotes[j], &content->g_collector);
// 			j++;
// 		}
// 		cmds[i] = hold;
// 		printf("(%s)\n", hold);
// 		i++;
// 	}
// 	return (cmds);
// }

static void	echo(t_container *content, t_data *current)
{
	int	i;
	int	new_line;
	int	espace;
	char **cmd;

	espace = 0;
	new_line = 0;
	expanding_cmds_redirections(content, &current->befor_expanding, NULL, 1);
	cmd = ft_spl(current->befor_expanding, ' ', &content->g_collector);
	int j = 0;
	while (cmd[j])
	{
		printf("(%s%d)\n", cmd[j], j);
		j++;
	}
	
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
	saved_stdout = rideraction_builtins(current);
	
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
			exit(1);
		}
		close(saved_stdout);
	}
}
