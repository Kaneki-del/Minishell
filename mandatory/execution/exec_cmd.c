/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/23 10:16:15 by sait-nac         ###   ########.fr       */
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

char	**env_to_array(t_env *head, t_gc **g_collector)
{
	t_env	*temp;
	int		count;
	char	**env_array;
	char	*tem;
	int		i;

	temp = NULL;
	count = 0;
	temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
	{
		perror("malloc failed");
		exit(1);
	}
	temp = head;
	tem = NULL;
	i = 0;
	while (temp)
	{
		tem = ft_str_join(temp->key, "=", g_collector);
		env_array[i] = ft_str_join(tem, temp->value, g_collector);
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

void	executing(t_env *env_list, char **cmd_args, t_gc **gc)
{
	char	*cmd_path;
	char	**list_char;

	if (!env_list)
		exit(127);
	if (!cmd_args || !cmd_args[0])
	{
		print_error("Empty command");
		exit(127);
	}
	cmd_path = find_executable_path(env_list, cmd_args, gc);
	list_char = env_to_array(env_list, gc);
	if (cmd_args)
	{
		if (execve(cmd_path, cmd_args, list_char) == -1)
		{
			print_error(cmd_args[0]);
			exit(127);
		}
	}
	exit(127);
}
