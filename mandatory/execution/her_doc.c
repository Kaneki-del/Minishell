/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:30:14 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/21 00:58:15 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	hrdc_ctrlc(int fd, t_container *content)
{
	if (g_sig)
	{
		content->status = 1;
		if (dup2(fd, 0) == -1)
		{
			perror("error in dup2");
			clear_bin(&content->g_collector);
			clear_bin(&content->g_env_collector);
			clean_fds(content->data);
			exit(1);
		}
		close(fd);
		return (-3);
	}
	content->status = 0;
	return (0);
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
