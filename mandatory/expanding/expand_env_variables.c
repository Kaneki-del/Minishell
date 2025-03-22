/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:03:03 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/21 22:05:16 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *exit_status(t_container *content, int *i)
{
    char *res;

    if (!content)
        return (NULL);
    (*i)++;
    res = ft_itoa(content->status, &content->g_collector);
    if (!res)
        return (NULL);
    return (res);
}

static char *expand_telda(char *command, int *i, t_container *content)
{
    t_env *pair;

    pair = NULL;
    if (command[(*i)] == '~' && \
    ((command[(*i) + 1] == ' ' || command[(*i) + 1] == '\0' \
    || command[(*i) + 1] == '/') && ((*i) == 0 || command[(*i) - 1] == ' ' \
    || (ft_strncmp(command, "export ", 7) == 0 \
    && command[(*i) - 1] == '='))))
    {
        (*i)++;
        pair = check_if_there("HOME", &content->env_list);
        if (!pair)
            return (ft_strdup("", &content->g_collector));
        return (pair->value);
    }
    return (NULL);
}

char  *check_expanding_variables(t_container *content, char *command, int *i, char qoute)
{
    char *expanded_part;

    expanded_part = NULL;
    (*i)++;
    if (!ft_isalpha(command[(*i)]) || qoute == '"')
        content->flag = 3;
    if (command[(*i)] == '?')
    {
        (*i)++;
        content->new_command = ft_strjoin(content->new_command, \
        ft_itoa(content->status, &content->g_collector), &content->g_collector);
        return (expanded_part);//----------
    }
    else if (((ft_isdigit(command[(*i)]) || (!ft_isalpha(command[(*i)]) && \
    command[(*i)] != '_')) && (command[(*i)] != '"' && command[(*i)] != '\'' )))
        (*i)++;
    else if (ft_isalpha(command[(*i)]) || command[(*i)] == '_')
    {
        expanded_part = expand(content, command, i, 0);
        if (expanded_part)
            content->new_command = ft_strjoin(content->new_command, \
            expanded_part, &content->g_collector);
        return (expanded_part);
    }
    return (NULL);
}

int check_expanding_telda(t_container *content, char *command, t_vars *vars, char qoute)
{
    char *expanded_part;

    expanded_part = NULL;
    if(qoute != '"' && qoute != '\'' && command[vars->i] == '~' && !vars->inexpand_here)
    {
        expanded_part = expand_telda(command, &vars->i, content);
        if (expanded_part)
        {
            content->new_command = ft_strjoin(content->new_command, expanded_part, &content->g_collector);
            return (1);
        }
    }
    return (0);
}

int finding_and_expanding(t_container *content, char *command, t_vars *vars, char qoute)
{
    if (content->flag == 1 && command[vars->i] == '<' && command[vars->i + 1] == '<' && !vars->is_in)
        vars->inexpand_here = 1;
    if (content->shoud_skeep && (((command[vars->i] == '"' || command[vars->i] == '\'') \
    && qoute == command[vars->i] && vars->is_in) || ((command[vars->i] == '"' \
    || command[vars->i] == '\'') && !vars->is_in)))
        return (vars->i++, 1);
    if (command[vars->i] == '$' && qoute != '\'' && command[vars->i + 1] != qoute \
    && (ft_isalnum(command[vars->i + 1]) || command[vars->i + 1] == '\'' \
    || command[vars->i + 1] == '"' || command[vars->i + 1] == '?' \
    || command[vars->i + 1] == '_'))
    {
        if ((command[vars->i] && qoute == '"' && command[vars->i + 1] == '\'') || \
        (vars->inexpand_here && command[vars->i + 1] != '\''  && command[vars->i + 1] != '"' ))
            ;
        else
        {
            check_expanding_variables(content, command, &vars->i, qoute); 
            return (1);
        }
    }
    if (check_expanding_telda(content, command, vars, qoute) == 1)
        return (1);
    return (0);
}
// the first this is the epandable string shoud starts with $ and end with special character 
char *check_env_var(t_container *content, char *command)
{
    char qoute;
    t_vars vars;

    vars.i = 0;
    vars.inexpand_here = 0;
    vars.is_in = 0;
    if (!command)
        return (NULL);
    qoute = '\0';
    content->new_command = NULL;
    while (command[vars.i])
    {
        qoute = in_quotations(command, &vars.i, qoute, &vars.is_in);
        if (finding_and_expanding(content, command, &vars, qoute))
            continue;
        content->new_command = ft_strchr_join(content->new_command, command[vars.i], &content->g_collector);
        vars.i++;
    }
    return (content->new_command);
}

