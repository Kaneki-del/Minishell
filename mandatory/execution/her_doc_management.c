/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:45:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/24 23:18:04 by sait-nac         ###   ########.fr       */
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

	line_tmp = readline("> ");
	if (line_tmp == NULL || g_sig)
		return (NULL);
	line = ft_strdup(line_tmp, &content->g_collector, content);
	free(line_tmp);
	if (ft_strcmp(line, remove_quotes(limiter, &content->g_collector,
				content)) == 0)
		return (NULL);
	else if (!ft_strchr(limiter, '"') && !ft_strchr(limiter, '\'') && \
	limiter[0] != '\0')
		line = expand_here_doc_lines(content, line);
	tmp = ft_strjoin(line, "\n", &content->g_collector, content);
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
		final = ft_strjoin(final, tmp, &content->g_collector, content);
	}
	return (final);
}
