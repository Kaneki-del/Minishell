/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:48:40 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/08 23:10:32 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_pipe_check(t_token *iter, t_type_token CASE, t_container *content)
{
    int hold;

    hold = content->status;
    content->status = 258;
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_IN)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, &content->g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_OUT)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, &content->g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_HEREDOC)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, &content->g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_APPEND)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, &content->g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, &content->g_collector), 0);
    content->status = hold;
    return (1);
}
