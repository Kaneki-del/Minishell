/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:45:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/16 15:51:16 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_hrd(char *file)
{
	int	hdc;

	hdc = open(file, O_CREAT | O_RDWR, 0644);
	if (hdc == -1)
	{
		printf("Open() call failed[719]\n");
		return (-1);
	}
	return (hdc);
}

static char	*buffer_line(char *limiter, t_container *content)
{
	char	*line;
	char	*tmp;
	char	*line_tmp;
	line = readline("> ");
	if (line == NULL || g_sig)
		return (NULL);
	if (ft_strcmp(line, filer_qoutations(limiter, &content->g_collector)) == 0)
	{
		free(line);
		return (NULL);
	}
	else if ((check_is_in_qoutes(limiter) == 0) || (limiter[0] != '"'
			&& limiter[0] != '\'' && limiter[ft_strlen(limiter) - 1] != '"'
			&& limiter[ft_strlen(limiter) - 1] != '\''))
	{
		line_tmp = line;
		line = expand_here_doc_lines(content, line_tmp);
		free(line_tmp);
	}
	tmp = ft_strjoin(line, "\n", &content->g_collector);
	return (tmp);
}

void	fill_hdc_file(char *file, char *final, t_container *content)
{
	int	hrd;

	hrd = open_hrd(file);
	if (hrd == -1)
	{
		content->status = 1;
		return ;
	}
	if (final)
		write(hrd, final, ft_strlen(final));
	close(hrd);
}

char	*buffer_content(char *limiter, t_container *content)
{
	char	*tmp;
	char	*final;

	final = NULL;
	signal(SIGINT, ctrl_c_herdoc);
	while (!g_sig)
	{
		tmp = buffer_line(limiter, content);
		if (tmp == NULL)
			break ;
		final = ft_strjoin(final, tmp, &content->g_collector);
	}
	return (final);
}
