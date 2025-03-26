/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:42:51 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/26 16:57:16 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_list(t_container *content, t_data *list)
{
	t_env	*current;
	int		saved_stdout;

	saved_stdout = rideraction_builtins(list, content);
	if (!content->env_list)
		return ;
	current = content->env_list;
	while (current != NULL)
	{
		if (current->key && current->value && current->print_flag == 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
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

int	get_expanded_len(t_container *content, char *key)
{
	char	**hold;
	int		j;

	j = 0;
	hold = normal_ft_split(key, ' ', &content->g_collector, content);
	if (hold)
	{
		while (hold[j])
			j++;
	}
	return (j);
}

char	**fill_and_set_value(char **res, t_container *content, char **cmd, \
int *counter)
{
	int		i;
	int		j;
	char	*key;
	char	**hold;

	i = 0;
	while (cmd[i] != NULL)
	{
		cmd[i] = expand_and_remove(content, cmd[i], &key);
		if (cmd[i] && ((cmd[i][get_char_index(cmd[i], '=')] != '=' && content-> \
			flag == 5) || (content->flag == 5 && is_expanded_key(key))))
		{
			hold = normal_ft_split(cmd[i], ' ', &content->g_collector, content);
			if (hold)
			{
				j = 0;
				while (hold[j] != NULL)
					res[(*counter)++] = hold[j++];
			}
			i++;
		}
		else
			res[(*counter)++] = cmd[i++];
	}
	return (res);
}

void	handle_export(t_data *current, t_container *content)
{
	int		i;
	int		counter;
	char	**cmd;
	char	**res;

	counter = 0;
	cmd = ft_split(current->befor_expanding, ' ', &content->g_collector, \
		content);
	res = split_and_expand(content, cmd, &counter);
	counter = 0;
	res = fill_and_set_value(res, content, cmd, &counter);
	res[counter] = NULL;
	current->cmds = res;
	i = 0;
	if (!current->cmds)
		return ;
	while (current->cmds[i])
		i++;
	if (i == 1)
		print_export(current, content);
	else
		add_export(content->data->cmds + 1, content);
}

void	built_in(t_data *current, t_container *content)
{
	if (ft_strcmp(current->cmds[0], "env") == 0)
		print_env_list(content, content->data);
	else if (ft_strcmp(current->cmds[0], "export") == 0)
		handle_export(current, content);
	else if (ft_strcmp(current->cmds[0], "unset") == 0)
		handle_unset(current->cmds, content, current);
	else if (ft_strcmp(current->cmds[0], "echo") == 0)
		handle_echo(content, current);
	else if (ft_strcmp(current->cmds[0], "pwd") == 0)
		handle_pwd(content, current);
	else if (ft_strcmp(current->cmds[0], "cd") == 0)
		handle_cd(current, content);
	else if (ft_strcmp(current->cmds[0], "exit") == 0)
		handle_exit(current, content);
}
