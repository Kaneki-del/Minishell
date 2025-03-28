/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expanding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:38:51 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/26 17:18:23 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	here_doc_expander(t_container *content, char *command, \
char **new_command, int *i)
{
	char	*curent_part;

	curent_part = NULL;
	(*i)++;
	if (command[(*i)] == '?')
	{
		(*i)++;
		*new_command = ft_strjoin(*new_command, ft_itoa(content->status, \
		content), &content->g_collector, content);
		return (1);
	}
	else if (((ft_isdigit(command[(*i)]) || (!ft_isalpha(command[(*i)]) \
	&& command[(*i)] != '_'))))
		(*i)++;
	else if (ft_isalnum(command[(*i)]) || command[(*i)] == '_')
	{
		curent_part = expand(content, command, i, 1);
		if (curent_part)
			*new_command = ft_strjoin(*new_command, curent_part, \
			&content->g_collector, content);
		return (1);
	}
	return (0);
}

char	*expand_here_doc_lines(t_container *content, char *command)
{
	int		i;
	char	*new_command;

	if (!command)
		return (NULL);
	i = 0;
	new_command = NULL;
	while (command[i])
	{
		if (command[i] == '$' && (ft_isalnum(command[i + 1]) \
		|| command[i + 1] == '?' || command[i + 1] == '_'))
		{
			if (here_doc_expander(content, command, &new_command, &i) == 1)
				continue ;
		}
		new_command = ft_strchr_join(new_command, command[i], content);
		i++;
	}
	return (new_command);
}

char	*expand_and_remove(t_container *content, char *cmd, char **key)
{
	*key = cmd;
	cmd = expanding_cmds_redirections(content, cmd, NULL, 3);
	if (cmd && cmd[0] == '\0')
		cmd = NULL;
	cmd = remove_quotes(cmd, &content->g_collector, content);
	return (cmd);
}

char	**split_and_expand(t_container *content, char **cmd, int *counter)
{
	char	*key;
	char	**res;
	int		i;

	i = 0;
	*counter = 0;
	while (cmd[i])
	{
		key = expanding_cmds_redirections(content, cmd[i], NULL, 3);
		if (key && key[0] == '\0')
			key = NULL;
		key = remove_quotes(key, &content->g_collector, content);
		if (key && ((key[get_char_index(key, '=')] != '=' && content-> \
			flag == 5) || (content->flag == 5 && is_expanded_key(cmd[i]))))
			(*counter) += get_expanded_len(content, key);
		else
			(*counter)++;
		i++;
	}
	res = gc((sizeof(char *) * (*counter + 1)), &content->g_collector, content);
	return (res);
}

int	is_expanded_key(char *str)
{
	int	i;
	int	has_dollar;

	i = 0;
	has_dollar = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			has_dollar = 1;
		if (str[i] == '=')
			return (has_dollar);
		i++;
	}
	return (0);
}
