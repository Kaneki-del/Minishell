/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:23:32 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 17:49:12 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	token_split(t_container *content, int *i)
{
	if (content->line[(*i)] == '<' && content->line[(*i) + 1] == '<')
	{
		ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup("<<", \
		&content->g_collector, content), T_REDIRECTE_HEREDOC, content));
		(*i)++;
	}
	else if (content->line[(*i)] == '>' && content->line[(*i) + 1] == '>')
	{
		ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup(">>", \
		&content->g_collector, content), T_REDIRECTE_APPEND, content));
		(*i)++;
	}
	else if (content->line[(*i)] == '<')
		ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup("<", \
		&content->g_collector, content), T_REDIRECTE_IN, content));
	else if (content->line[(*i)] == '>')
	{
		ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup(">", \
		&content->g_collector, content), T_REDIRECTE_OUT, content));
		if (content->line[(*i) + 1] == '|')
			(*i)++;
	}
	else if (content->line[(*i)] == '|')
		ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup("|", \
		&content->g_collector, content), T_PIPE, content));
}

static int	check_is_syntax_err(int is_in, char qoute, t_container *content)
{
	if (is_in == 1)
	{
		content->status = 258;
		return (ft_error("mshell: syntax error near unexpected token", \
		ft_chrjoin(qoute, '\0', content), 2), 0);
	}
	return (1);
}

static int	skeep_special_char(t_container *content, int *start)
{
	int		is_in;
	char	qoute;

	is_in = 0;
	while (content->line[(*start)] && !ft_strchr("<|>", \
	content->line[(*start)]) && !ft_strchr(" \n\t", content->line[(*start)]))
	{
		if (content->line[(*start)] == '\'' || content->line[(*start)] == '"')
		{
			qoute = content->line[(*start)];
			(1) && ((*start)++, is_in = 1);
			while (content->line[(*start)] && content->line[(*start)] != qoute)
				(*start)++;
			if (content->line[(*start)] == qoute)
				(1) && ((*start)++, is_in = 0);
		}
		while (content->line[(*start)] && (content->line[(*start)] != '\'' && \
		content->line[(*start)] != '"') && \
		!ft_strchr("<|>", content->line[(*start)]) && \
		!ft_strchr(" \n\t", content->line[(*start)]))
			(*start)++;
	}
	if (check_is_syntax_err(is_in, qoute, content) == 0)
		return (0);
	return (1);
}

int	tokener(t_container *content)
{
	int		i;
	int		start;
	char	*word;

	i = -1;
	word = NULL;
	while (content->line[++i])
	{
		if (ft_strchr(" \n\t", content->line[i]))
			continue ;
		token_split(content, &i);
		if (content->line[i] && !ft_strchr("<|>", content->line[i]) && \
		!ft_strchr(" \n\t", content->line[i]))
		{
			start = i;
			if (skeep_special_char(content, &start) == 0)
				return (0);
			word = gc(start - i + 1, &content->g_collector, content);
			ft_strlcpy(word, &content->line[i], start - i + 1);
			ft_lstadd_back(&content->tokens, ft_lstnew(word, T_WORD, \
			content));
			i = start - 1;
		}
	}
	return (1);
}

int	token_checker(t_container *content)
{
	t_token	*iter;

	if (!content->tokens)
		return (0);
	iter = content->tokens;
	if (check_is_pipe_first(iter, content, 1) == 0)
		return (0);
	while (iter && iter->next)
	{
		if (check_is_pipe_first(iter, content, 0) == 0)
			return (0);
		if (redirection_pipe_check(iter, T_REDIRECTE_IN, content) == 0)
			return (0);
		if (redirection_pipe_check(iter, T_REDIRECTE_OUT, content) == 0)
			return (0);
		if (redirection_pipe_check(iter, T_REDIRECTE_APPEND, content) == 0)
			return (0);
		if (redirection_pipe_check(iter, T_REDIRECTE_HEREDOC, content) == 0)
			return (0);
		iter = iter->next;
	}
	if (check_is_last_redirection(iter, content) == 0)
		return (0);
	return (1);
}
