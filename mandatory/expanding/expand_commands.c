/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 03:19:18 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/24 17:28:24 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**export_cases(char **only_command, char **cmd_options, \
t_container *content)
{
	if (cmd_options[1] && cmd_options[1][get_char_index(cmd_options[1], \
	'=') + 1] == '"' && cmd_options[1][ft_strlen(cmd_options[1]) - 1] == '"')
		*only_command = remove_quotes(*only_command, &content->g_collector, \
		content);
	cmd_options = ft_split(*only_command, ' ', &content->g_collector, content);
	if (cmd_options[1])
	{
		cmd_options[1] = ft_strdup(*only_command + 7, &content->g_collector, \
		content);
		cmd_options[2] = NULL;
	}
	return (cmd_options);
}

char	**prepare_export_command(char **only_command, char **cmd_options, \
t_container *content)
{
	if (ft_strlen_2d(cmd_options) < 3)
	{
		if (cmd_options && cmd_options[1] && cmd_options[1][0] == '$')
			cmd_options = normal_ft_split(*only_command, ' ', \
			&content->g_collector, content);
		else
		{
			if (ft_strcmp(cmd_options[0], "export") == 0)
				cmd_options = export_cases(only_command, cmd_options, content);
			else
			{
				cmd_options = ft_split(*only_command, ' ', \
				&content->g_collector, content);
				cmd_options = prepare_export_command(only_command, \
				cmd_options, content);
			}
		}
	}
	else
		cmd_options = normal_ft_split(*only_command, ' ', \
		&content->g_collector, content);
	return (cmd_options);
}

char	**prepare_commands(char **only_command, char *old_cmd, \
char **cmd_options, t_container *content)
{
	if (!only_command || !*only_command)
		return (NULL);
	if (*only_command && ft_strncmp(*only_command, "export ", 7) == 0 && \
	content->flag == 5)
	{
		cmd_options = ft_split(old_cmd, ' ', &content->g_collector, content);
		if (!cmd_options || !cmd_options[0])
			return (NULL);
		cmd_options = \
		prepare_export_command(only_command, cmd_options, content);
	}
	else
	{
		if (content->flag == 5)
			cmd_options = ft_split(*only_command, ' ', &content->g_collector, \
			content);
		else
			cmd_options = filter_all(ft_split(*only_command, ' ', \
			&content->g_collector, content), &content->g_collector, content);
	}
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
