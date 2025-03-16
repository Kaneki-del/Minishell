/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:30:14 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/16 00:30:35 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_file(t_gc **g_collector)
{
	char	*file_name;
	int		i;

	i = 0;
	while (1)
	{
		file_name = ft_strjoin("/tmp/.her_doc", ft_itoa(i, g_collector),
				g_collector);
		if (access(file_name, F_OK) == -1)
			return (file_name);
		i++;
	}
}

char	*buffer_line(char *limiter, t_container *content)
{
	char	*line;
	char	*tmp;

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
		line = expand_here_doc_lines(content, line);
	tmp = ft_strjoin(line, "\n", &content->g_collector);
	return (tmp);
}

int	hrdc_ctrlc(int fd, t_container *content)
{
	if (g_sig)
	{
		content->status = 1;
		if (dup2(fd, 0) == -1)
		{
			printf("error in dup\n");
			return (-3);
		}
		close(fd);
		return (-3);
	}
	content->status = 0;
	return (0);
}

static char	*buffer_content(char *limiter, t_container *content)
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

int	open_hrd(char *file)
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

static void	fill_hdc_file(char *file, char *final, t_container *content)
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

int	end_hdc(int fd, char *file)
{
	int	hdc;

	close(fd);
	hdc = open(file, O_CREAT | O_RDWR, 0644);
	if (hdc == -1)
	{
		ft_putstr_fd("Open() call failed[013]\n", 2);
		unlink(file);
		return (-1);
	}
	unlink(file);
	return (hdc);
}

int	her_doc(char *limiter, t_container *content)
{
	int		fd;
	char	*file_name;
	char	*final;
	int		hdc;

	fd = dup(0);
	if (fd == -1)
		return (-1);
	final = buffer_content(limiter, content);
	if (hrdc_ctrlc(fd, content) == -3)
		return (-3);
	file_name = get_file(&content->g_collector);
	fill_hdc_file(file_name, final, content);
	hdc = end_hdc(fd, file_name);
	return (hdc);
}
