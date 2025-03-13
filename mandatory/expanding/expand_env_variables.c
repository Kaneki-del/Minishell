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

static char *expand_telda(char *command, int *i, t_env **env_list)
{
    t_env *pair;

    pair = NULL;
    if (command[(*i)] == '~' && \
    ((command[(*i) + 1] == ' ' || command[(*i) + 1] == '\0' || command[(*i) + 1] == '/')\
    && ((*i) == 0 || command[(*i) - 1] == ' ' || (ft_strncmp(command, "export ", 7) == 0 \
    && command[(*i) - 1] == '='))))
    {
        (*i)++;
        pair = check_if_there("HOME", env_list);
        if (!pair)
            return (NULL);
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
        return (expanded_part);
    }
    else if (((ft_isdigit(command[(*i)]) || (!ft_isalpha(command[(*i)]) && command[(*i)] != '_')) \
    && (command[(*i)] != '"' && command[(*i)] != '\'' )))
        (*i)++;
    else if (ft_isalnum(command[(*i)]) || command[(*i)] == '_')
    {
        expanded_part = expand(content, command, i);
        if (expanded_part)
            content->new_command = ft_strjoin(content->new_command, expanded_part, &content->g_collector);
        return (expanded_part);
    }
    return (NULL);
}

int finding_and_expanding(t_container *content, char *command, int *i, char qoute)
{
    char *expanded_part;

    expanded_part = NULL;
    if (command[(*i)] == '$' && qoute != '\'' && command[(*i) + 1] != qoute && (ft_isalnum(command[(*i) + 1]) \
    || command[(*i) + 1] == '\''  || command[(*i) + 1] == '"' || command[(*i) + 1] == '?' || command[(*i) + 1] == '_'))
    {
        if (command[(*i)] && qoute == '"' && command[(*i) + 1] == '\'')
            ;
        else
        {
            check_expanding_variables(content, command, i, qoute);
            return (1);
        }
    }
    else if(qoute != '"' && qoute != '\'' && command[(*i)] == '~')
    {
        expanded_part = expand_telda(command, i, &content->env_list);
        if (expanded_part)
        {
            content->new_command = ft_strjoin(content->new_command, expanded_part, &content->g_collector);
            return (1);
        }
    }
    return (0);
}
// the first this is the epandable string shoud starts with $ and end with special character 
char *check_env_var(t_container *content, char *command)
{
    int i;
    int is_in;
    char qoute;

    if (!command)
        return (NULL);
    i = 0;
    is_in = 0;
    qoute = '\0';
    content->new_command = NULL;
    while (command[i])
    {
        qoute = in_quotations(command, &i, qoute, &is_in);
        if (finding_and_expanding(content, command, &i, qoute))
            continue;
        content->new_command = ft_strchr_join(content->new_command, command[i], &content->g_collector);
        i++;
    }
    return (content->new_command);
}

