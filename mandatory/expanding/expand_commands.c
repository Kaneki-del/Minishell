/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 03:19:18 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/27 10:32:54 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**prepare_commands(char **only_command, \
char **cmd_options, t_container *content)
{
	if (!only_command || !*only_command)
		return (NULL);
	if (content->flag == 5)
		cmd_options = ft_split(*only_command, ' ', &content->g_collector, \
		content);
	else
		cmd_options = filter_all(ft_split(*only_command, ' ', \
		&content->g_collector, content), &content->g_collector, content);
	return (cmd_options);
}

char	*expanding_cmds_redirections(t_container *content, char *only_command, \
char *dir_files, int shoud_skeep)
{
	content->shoud_skeep = shoud_skeep;
	if (only_command)
	{
		content->flag = 2;
		return (check_env_var(content, only_command));
	}
	if (dir_files)
	{
		content->flag = 1;
		return (check_env_var(content, dir_files));
	}
	return (NULL);
}

int	pair_check_cases(t_container *content, t_env *pair, char *key, \
int is_here_doc)
{
	if (!pair || !pair->value || pair->value[0] == '\0' \
	|| pair->print_flag == 3)
	{
		if (content->flag == 1 && !is_here_doc)
		{
			ft_error_exec_two("mshell: $", key, ": ambiguous redirect", 2);
			content->flag = 0;
			content->status = 1;
		}
		return (1);
	}
	if (!is_here_doc && pair && content->flag == 1 && pair->value && \
	(words_count(remove_quotes(pair->value, &content->g_collector, \
	content), ' ') > 1))
	{
		ft_error_exec_two("mshell: $", key, ": ambiguous redirect", 2);
		content->flag = 0;
		content->status = 1;
		return (1);
	}
	return (0);
}
