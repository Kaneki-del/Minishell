/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:48:40 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/25 10:16:00 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_pipe_check(t_token *iter, t_type_token CASE, t_gc **g_collector)
{
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_IN)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_OUT)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_HEREDOC)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_REDIRECTE_APPEND)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == CASE && iter->next->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    return (1);
}
