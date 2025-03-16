/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:48:40 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/16 14:19:29 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_pipe_check(t_token *iter, t_type_token CASE, t_container *content)
{
    int hold;

    hold = content->status;
    content->status = 258;
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_IN)
        return (ft_error("mshell: syntax error near unexpected token", iter->next->value, 2), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_OUT)
        return (ft_error("mshell: syntax error near unexpected token", iter->next->value, 2), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_HEREDOC)
        return (ft_error("mshell: syntax error near unexpected token", iter->next->value, 2), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_APPEND)
        return (ft_error("mshell: syntax error near unexpected token", iter->next->value, 2), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_PIPE)
        return (ft_error("mshell: syntax error near unexpected token", iter->next->value, 2), 0);
    content->status = hold;
    return (1);
}

int check_is_last_redirection(t_token *iter, t_container *content)
{
	if (iter->next == NULL && (iter->token_type == T_PIPE || \
	iter->token_type == T_REDIRECTE_IN || iter->token_type == T_REDIRECTE_OUT \
	|| iter->token_type == T_REDIRECTE_APPEND || iter->token_type == T_REDIRECTE_HEREDOC))
	{
			content->status = 258;
			return (ft_error("mshell: syntax error near unexpected token", "newline", 2), 0);
	}
	return (1);
}

int check_is_pipe_first(t_token *iter, t_container *content, int flag)
{
	if (flag)
	{
		if (iter->token_type == T_PIPE)
		{
			content->status = 258;
			return (ft_error("mshell: syntax error near unexpected token", "|", 2), 0);
		}
	}
	else
	{
		if (iter->token_type == T_PIPE && iter->next->token_type == T_PIPE)
		{
			content->status = 258;
			return (ft_error("mshell: syntax error near unexpected token", iter->next->value, 2), 0);
		}
	}
	return (1);
}