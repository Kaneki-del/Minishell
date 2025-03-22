/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:30:14 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 15:07:53 by kben-tou         ###   ########.fr       */
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
			close(fd);
			perror("error in dup2");
			clean_exit2(content, 1);
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

char	*get_file(t_container *content)
{
	char	*file_name;
	int		i;

	i = 0;
	while (1)
	{
		file_name = ft_strjoin("/tmp/.her_doc",
				ft_itoa(i, content), &content->g_collector,
				content);
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
	{
		perror("error in dup");
		clean_exit2(content, 1);
	}
	final = buffer_content(limiter, content);
	if (hrdc_ctrlc(fd, content) == -3)
		return (-3);
	file_name = get_file(content);
	fill_hdc_file(file_name, final, content);
	hdc = end_hdc(fd, file_name);
	return (hdc);
}
