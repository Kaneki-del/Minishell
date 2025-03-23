/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 03:01:19 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 22:45:03 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_outputs(char **dir_files, t_token *token, t_container *content)
{
	*dir_files = ft_strjoin(*dir_files, token->value, \
	&content->g_collector, content);
	if (token->next != NULL)
		*dir_files = ft_strjoin(*dir_files, " ", \
		&content->g_collector, content);
	*dir_files = ft_strjoin(*dir_files, token->next->value, \
	&content->g_collector, content);
	if (token->next->next != NULL)
		*dir_files = ft_strjoin(*dir_files, " ", \
		&content->g_collector, content);
}

void	get_dir_files(char **dir_files, t_token *token, t_container *content)
{
	if (!token || !token->next)
		return ;
	if ((token->token_type == T_REDIRECTE_IN || \
	token->token_type == T_REDIRECTE_HEREDOC) && token->token_type != T_PIPE)
		get_outputs(dir_files, token, content);
	else if ((token->token_type == T_REDIRECTE_OUT || \
	token->token_type == T_REDIRECTE_APPEND) && \
	token->token_type != T_PIPE)
		get_outputs(dir_files, token, content);
}

void	get_command(char **only_command, t_token *token, t_container *content)
{
	static int	input_check;
	static int	output_check;

	if (token->token_type == T_REDIRECTE_OUT \
	|| token->token_type == T_REDIRECTE_APPEND)
		output_check = 1;
	else if (token->token_type == T_REDIRECTE_IN \
	|| token->token_type == T_REDIRECTE_HEREDOC)
		input_check = 1;
	else if (token->token_type == T_WORD && \
	(input_check == 1 || output_check == 1))
		(1) && (input_check = 0, output_check = 0);
	else if (token->token_type == T_WORD && \
	(input_check == 0 || output_check == 0))
	{
		*only_command = ft_strjoin(*only_command, token->value, \
		&content->g_collector, content);
		if (token && token->next && token->next->token_type != T_PIPE)
			*only_command = ft_strjoin(*only_command, " ", \
			&content->g_collector, content);
	}
}
