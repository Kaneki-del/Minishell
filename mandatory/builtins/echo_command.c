/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:53:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/20 17:15:04 by kben-tou         ###   ########.fr       */
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
int is_only_space(char *cmd)
{
	int j = 0;
	if (!cmd)
		return (0);
	while (cmd[j])
	{
		if (cmd[j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

char **prepare_last_command(t_container *content, char **temp_cmd, char **cmd)
{
	int j = 0;
	size_t count;
	int i;

	count = 0;
	while (temp_cmd[j])
	{
		if (is_only_space(temp_cmd[j]))
			count++;
		j++;
	}
	cmd = gc((sizeof(char *) * (count + 1)), &content->g_collector);
	if (!cmd)
		return (NULL);
	j = 0;
	i = 0;
	while (temp_cmd[j])
	{
		if (is_only_space(temp_cmd[j]) == 1)
		{
			printf("(%s)\n", temp_cmd[j]);
			cmd[i] = temp_cmd[j];
			if (!cmd[i])
				return (NULL);
			i++;	
		}	
		j++;
	}
	cmd[i] = NULL;
	return (cmd);
}

static void	echo(t_container *content, t_data *current)
{
	int	i;
	int	new_line;
	int	espace;
	// char **temp_cmd;
	char **cmd;
	char *old_cmd;

	espace = 0;
	new_line = 0;
	cmd = NULL;
	old_cmd = ft_strdup(current->befor_expanding, &content->g_collector);
	expanding_cmds_redirections(content, &current->befor_expanding, NULL, 0);
	cmd = ft_split(current->befor_expanding, ' ', &content->g_collector);
	int j = 0;
	while (cmd[j])
	{
		if (ft_strchr(old_cmd, '"') || ft_strchr(old_cmd, '\''))
			cmd[j] = remove_quotes(cmd[j], &content->g_collector);
		j++;
	}
	
	// if (!temp_cmd || !temp_cmd[0])
	// 	return ;
	// cmd = prepare_last_command(content, temp_cmd, cmd);
	// if (!cmd || !cmd[0])
	// 	return ;
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
