
#include "../../includes/minishell.h"

char check_in_qoutation(char c)
{
    static int is_in;
    static char qoute;

    if (c == '\'' || c == '"')
    {
        if (!is_in)
        {
            is_in = 1;
            qoute = c;
        }
        else if (is_in && c == qoute)
            is_in = 0;
    }
    return (qoute);
}

char *exit_status(t_container *content, int *i)
{
    (*i)++;
    return (ft_itoa(content->status, &content->g_collector));
}

char *expand(t_container *content, char *command, int *i)
{
    t_env *pair;
    char *key;
    int start;

    pair = NULL;
    key = NULL;
    // if (command[(*i)] == '\'' || command[(*i)] == '"')
    //     check_in_qoutation(command[(*i)]);
    if (command[(*i)] == '$' && check_in_qoutation(command[(*i)]) != '\'' && (command[(*i) + 1] == '_' || command[(*i) + 1] == '?' || ft_isalpha(command[(*i) + 1])))
    {
        (*i)++;
        if (command[(*i)] == '?')
            return (exit_status(content, i));
        start = (*i);
        while (command[start] && command[start] != ' ' && command[start] != '$' && \
        command[start] != '"' && command[start] != '\'')
            start++;
        key = gc(start - (*i) + 1, &content->g_collector);
        ft_strlcpy(key, &command[(*i)], start - (*i) + 1 );
        pair = check_if_there(key, &content->env_list);
        (*i) = start - 1;
        if (!pair)
            return (NULL);
        return (pair->value);
    }
    return (NULL);
}

char *expand_telda(char *command, int *i, t_env **env_list)
{
    t_env *pair;

    pair = NULL;
    if (command[(*i)] == '~' && !check_in_qoutation(command[(*i)]) && ((command[(*i) + 1] == ' ' \
    || command[(*i) + 1] == '\0') && (command[(*i) - 1] == ' ')))
    {
        (*i)++;
        pair = check_if_there("HOME", env_list);
        if (!pair)
            return (NULL);
        return (pair->value);
    }
    return (NULL);
}

char *check_env_var(t_container *content, char *command)
{
    int i;
    char *new_command;
    char *curent_part;

    i = 0;
    new_command = NULL;
    while (command[i])
    {
        curent_part  = expand(content, command, &i);
        if (curent_part)
        {
            new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
        }
        curent_part = expand_telda(command, &i, &content->env_list);
        if (curent_part)
        {
            new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
        }
        new_command = ft_strchr_join(new_command, command[i], &content->g_collector);
        i++;
    }
    return (new_command);
}

