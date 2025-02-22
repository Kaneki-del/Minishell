
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

char *exit_status(int *i, t_gc **g_collector, t_data **data)
{
    (*i)++;
    (void)data;
    int status = 0;
    char *s = ft_itoa(status, g_collector);
    return (s);
}

char *expand(char *command, int *i, t_env **env_list, t_gc **g_collector, t_data **data )
{
    t_env *pair;
    char *key;
    int start;

    pair = NULL;
    key = NULL;
    if (command[(*i)] == '$' && check_in_qoutation(command[(*i)]) != '\'' && \
    (command[(*i) + 1] == '_' || command[(*i) + 1] == '?' || ft_isalpha(command[(*i) + 1])))
    {
        (*i)++;
        if (command[(*i)] == '?')
            return (exit_status(i, g_collector, data));
        start = (*i);
        while (command[start] && command[start] != ' ' && command[start] != '$' && command[start] != '"' && command[start] != '\'')
            start++;
        key = gc(start - (*i) + 1, g_collector);
        ft_strlcpy(key, &command[(*i)], start - (*i) + 1 );
        printf("(( %s ))\n", key);
        pair = check_if_there(key, env_list);
        (*i) = start;
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

char *check_env_var(char *command, t_env **env_list, t_gc **g_collector, t_data **data)
{
    int i;
    char *new_command;
    char *curent_part;

    i = 0;
    new_command = NULL;
    while (command[i])
    {
        check_in_qoutation(command[i]);
        curent_part  = expand(command, &i, env_list, g_collector, data);
        if (curent_part)
        {
            new_command = ft_strjoin(new_command, curent_part, g_collector);
            continue ;
        }
        curent_part = expand_telda(command, &i, env_list);
        if (curent_part)
        {
            new_command = ft_strjoin(new_command, curent_part, g_collector);
            continue ;
        }
        new_command = ft_strchr_join(new_command, command[i], g_collector);
        i++;
    }
    return (new_command);
}

