/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/23 19:14:19 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_lent;
	size_t	src_lent;
	size_t	i;

	i = 0;
	src_lent = ft_strlen(src);
	if (dstsize == 0)
		return (src_lent);
	dst_lent = ft_strlen(dst);
	if (dst_lent >= dstsize)
		return (dstsize + src_lent);
	while (i < (dstsize - dst_lent - 1) && src[i])
	{
		dst[dst_lent + i] = src[i];
		i++;
	}
	dst[dst_lent + i] = '\0';
	return (dst_lent + src_lent);
}
char	*ft_str_join(char const *s1, char const *s2, t_gc **gc)
{
	size_t	total_len;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, gc));
	if (!s2)
		return (ft_strdup(s1, gc));
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(total_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len);
	ft_strlcat(result, s2, total_len);
	return (result);
}

char	**env_to_array(t_container *content)
{
	t_env	*temp;
	int		count;
	char	**env_array;
	char	*tem;
	int		i;

	temp = NULL;
	count = 0;
	temp = content->env_list;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = gc((count + 1) * sizeof(char *), &content->g_collector);
	if (!env_array)
	{
		perror("malloc failed");
		exit(1);
	}
	temp = content->env_list;
	tem = NULL;
	i = 0;
	while (temp)
	{
		tem = ft_str_join(temp->key, "=", &content->g_collector);
		env_array[i] = ft_str_join(tem, temp->value, &content->g_collector);
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	print_error(char *cmd_input)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd_input, 2);
	exit(127);
}

void	executing(t_container *content)
{
	char	*cmd_path;
	char	**list_char;

	if (!content->env_list)
		exit(127);
	if (!content->data->cmds || !content->data->cmds[0])
	{
		print_error("Empty command");
		exit(127);
	}
	cmd_path = find_executable_path(content);
	list_char = env_to_array(content);
	if (content->data->cmds)
	{
		if (execve(cmd_path, content->data->cmds, list_char) == -1)
		{
			print_error(content->data->cmds[0]);
			exit(127);
		}
	}
	exit(127);
}
