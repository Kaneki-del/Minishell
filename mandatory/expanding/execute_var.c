
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

char *check_env_var(char *command, t_env **env_list, t_gc **g_collector)
{
    int i;
    int start;
    char *key;
    char *new_command;
    t_env *pair;

    (void)env_list;
    (void)g_collector;
    i = 0;
    start = 0;
    key = NULL;
    new_command = NULL;
    pair = NULL;
    if (!command)
        return (NULL);
    while (command[i])
    {
        check_in_qoutation(command[i]);
        if (command[i] == '$' && check_in_qoutation(command[i]) != '\'' && (command[i + 1] == '_' || ft_isalnum(command[i + 1])))
        {
            i++;
            start = i;
            while (command[start] && command[start] != ' ' && command[start] != '$' && command[start] != '"' && command[start] != '\'')
                start++;
            key = gc(start - i + 1, g_collector);
            ft_strlcpy(key, &command[i], start - i + 1 );
            pair = check_if_there(key, env_list);
            i = start;
            if (!pair)
                continue ;
            new_command = ft_strjoin(new_command, pair->value, g_collector);
            continue ;
        }
        else if (command[i] == '~' && (command[i + 1] == ' ' || command[i + 1] == '\0') && (command[i - 1] == ' ' || command[i - 1] == '\0'))
        {
            i++;
            pair = check_if_there("HOME", env_list);
            if (!pair)
                continue ;
            new_command = ft_strjoin(new_command, pair->value, g_collector);
        }
        new_command = ft_strchr_join(new_command, command[i], g_collector);
        i++;
    }
    return (new_command);
}

