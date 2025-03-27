/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:51:47 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/27 10:36:11 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_data(t_token *token, char **dir_files, \
char **only_command, t_container *content)
{
	*only_command = NULL;
	*dir_files = NULL;
	while (token && token->token_type != T_PIPE)
	{
		get_dir_files(dir_files, token, content);
		get_command(only_command, token, content);
		token = token->next;
	}
	if (token && token->token_type == T_PIPE && token->next)
		return (token->next);
	return (NULL);
}

void	init_norms(t_container *content, char *only_command, char **old_command)
{
	*old_command = only_command;
	content->is_status = content->status;
}

int	parser(t_container *content)
{
	t_token		*iter;
	char		*dir_files;
	char		*on_cmd;
	char		*old_command;
	char		**cmd_options;

	dir_files = NULL;
	on_cmd = NULL;
	cmd_options = NULL;
	iter = content->tokens;
	while (iter)
	{
		iter = init_data(iter, &dir_files, &on_cmd, content);
		init_norms(content, on_cmd, &old_command);
		on_cmd = expanding_cmds_redirections(content, on_cmd, NULL, 0);
		dir_files = expanding_cmds_redirections(content, NULL, dir_files, 0);
		if (content->flag == 0)
			return (0);
		cmd_options = prepare_commands(&on_cmd, cmd_options, content);
		add_data_back(&content->data, new_data_node(old_command, cmd_options, \
		filterd(ft_split(dir_files, ' ', &content->g_collector, content), \
		&content->g_collector, content), content));
	}
	return (1);
}

int	parsing_case(t_container *content)
{
	if (!content || !content->line)
		return (0);
	if (tokener(content) == 0)
		return (0);
	if (token_checker(content) == 0)
		return (0);
	if (parser(content) == 0)
		return (0);
	return (1);
}
