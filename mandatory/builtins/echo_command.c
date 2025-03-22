/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:53:15 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 14:05:58 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void echo(t_container *content, t_data *current)
{
    int i;
    int new_line;
    int espace;
    char **cmd;
    char *old_cmd;
    int j;

    espace = 0;
    new_line = 0;
    cmd = NULL;
    old_cmd = ft_strdup(current->befor_expanding, &content->g_collector);
    if (!old_cmd)
        return;
    content->status = content->is_status;
    expanding_cmds_redirections(content, &current->befor_expanding, NULL, 0);
    content->status = 0;

    // Split the command while preserving quoted parts
    cmd = split_preserving_quotes(current->befor_expanding, &content->g_collector);
    if (!cmd || !cmd[0])
        return;

    // Remove quotes only for variables that originally had quotes
    j = 0;
    while (cmd[j])
    {
        if (ft_strchr(old_cmd, '"') || ft_strchr(old_cmd, '\''))
            cmd[j] = remove_quotes(cmd[j], &content->g_collector);
        j++;
    }

    cmd = check_echo_options(cmd, &content->g_collector);
    if (!cmd || !cmd[0])
        return;

    i = 1;
    if (ft_strcmp(cmd[i], "-n") == 0)
    {
        i++;
        new_line = 1;
    }

    while (cmd[i])
    {
        if (espace == 1)
            write(1, " ", 1);
        ft_putstr_fd(cmd[i], 1);
        espace = 1;
        i++;
    }

    if (new_line == 0)
        write(1, "\n", 1);
}

// Helper function to split the command while preserving quoted parts
static char **split_preserving_quotes(char *str, t_collector *collector)
{
    char **result;
    int i = 0, j = 0, k = 0, in_quotes = 0;
    char quote_char = 0;

    result = ft_calloc(ft_strlen(str) / 2 + 2, sizeof(char *), collector);
    if (!result)
        return NULL;

    while (str[i])
    {
        if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
        {
            if (in_quotes && str[i] == quote_char)
                in_quotes = 0;
            else if (!in_quotes)
            {
                in_quotes = 1;
                quote_char = str[i];
            }
        }
        if (str[i] == ' ' && !in_quotes)
        {
            if (j != i)
                result[k++] = ft_substr(str, j, i - j, collector);
            while (str[i] == ' ')
                i++;
            j = i;
        }
        else
            i++;
    }
    if (j != i)
        result[k++] = ft_substr(str, j, i - j, collector);
    result[k] = NULL;

    return result;
}

// Helper function to remove quotes from a string
static char *remove_quotes(char *str, t_collector *collector)
{
    char *result;
    int i = 0, j = 0;

    result = ft_calloc(ft_strlen(str) + 1, sizeof(char), collector);
    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] != '"' && str[i] != '\'')
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';

    return result;
}

void	handle_echo(t_container *content, t_data *current)
{
	int		i;
	int		saved_stdout;
	char	**cmd;
	
	cmd = current->cmds;
	saved_stdout = rideraction_builtins(current, content);
	
	i = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
		echo(content, current);
	else
		write(1, "\n", 1);
	if (saved_stdout != -1)
	{
		if (dup2(saved_stdout, 1) == -1)
		{
			perror("error in dup2");
			clean_exit2(content, 1);
		}
		close(saved_stdout);
	}
}
