/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/28 10:16:20 by sait-nac         ###   ########.fr       */
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
// char	*ft_str_join(char const *s1, char const *s2, t_gc **gc)
// {
// 	size_t	total_len;
// 	char	*result;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2, gc));
// 	if (!s2)
// 		return (ft_strdup(s1, gc));
// 	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	result = (char *)malloc(total_len);
// 	if (!result)
// 		return (NULL);
// 	ft_strlcpy(result, s1, total_len);
// 	ft_strlcat(result, s2, total_len);
// 	return (result);
// }

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
	if (!temp)
		return NULL;
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
		tem = ft_strjoin(temp->key, "=", &content->g_collector);
		env_array[i] = ft_strjoin(tem, temp->value, &content->g_collector);
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

void	executing(t_data *current, t_container *content)
{
	char	*cmd_path;
	char	**list_char;

	//check what the bash do if no env list
	if (!content->env_list)
		exit(0);
	if (!current->cmds || !current->cmds[0])
		exit(0);
	cmd_path = find_executable_path(current, content);
	//bash: sd: command not found
	if (!cmd_path || ft_strcmp(current->cmds[0] , "\0") == 0)
	{
		ft_error_exec_two("bash: ", current->cmds[0], ": command not found", 2);
		exit(127);
	}	
	list_char = env_to_array(content);

	if (current->cmds)
	{
		if (execve(cmd_path, current->cmds, list_char) == -1)
		{
			ft_error_exec_two("bash: ", current->cmds[0], ": Is a directory", 2);
			exit(127);
		}
	}
}
