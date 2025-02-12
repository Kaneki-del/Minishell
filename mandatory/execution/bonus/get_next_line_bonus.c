/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:58:34 by sait-nac          #+#    #+#             */
/*   Updated: 2025/01/10 10:07:33 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*set_line(char **left)
{
	char	*result;
	size_t	i;
	size_t	st_lent;
	char	*rest_line;

	i = 0;
	while (((*left)[i] != '\n') && ((*left)[i] != '\0'))
		i++;
	if ((*left)[i] == 0 && !(*left)[0])
		return (free(*left), *left = NULL, NULL);
	if ((*left)[i] == '\n')
		i++;
	result = ft_substr(*left, 0, i);
	if (!result)
		return (free(*left), *left = NULL, NULL);
	st_lent = ft_strlen(*left + i);
	rest_line = ft_substr(*left, i, st_lent);
	free(*left);
	*left = rest_line;
	return (result);
}

static char	*get_the_line(int fd, char *left, char *buffer)
{
	ssize_t	check;
	char	*temp;

	check = 1;
	while (check > 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check < 0)
			return (NULL);
		buffer[check] = '\0';
		if (check == 0)
			break ;
		temp = left;
		left = ft_strjoin(temp, buffer, 'n');
		free(temp);
		if (!left)
			return (NULL);
		if (ft_strchr(left, '\n'))
			break ;
	}
	return (left);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*left;
	char		*final;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left);
		left = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(left), left = NULL, NULL);
	left = get_the_line(fd, left, buffer);
	free(buffer);
	buffer = NULL;
	if (!left)
		return (NULL);
	final = set_line(&left);
	if (!final)
		return (free(left), left = NULL, NULL);
	return (final);
}
