
#include "../../includes/minishell.h"

char check_in(char c)
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


char *expand_telda(char *command, int *i, t_env **env_list)
{
    t_env *pair;

    pair = NULL;
    if (command[(*i)] == '~'  && ((command[(*i) + 1] == ' ' || command[(*i) + 1] == '\0') && (command[(*i) - 1] == ' ' || command[0] == '~')))
    {
        (*i)++;
        pair = check_if_there("HOME", env_list);
        if (!pair)
            return (NULL);
        return (pair->value);
    }
    return (NULL);
}

int check_double(char *command, int i, char qoute)
{
    if (command[i] == '$' && qoute)
    {
        i++;
        while (command[i] == ' ' || command[i] == '\t')
            i++;
        if (command[i] == qoute)
            return (0);
    }
    return (1);
}

char *expand(t_container *content, char *command, int *i, int *flag)
{
    t_env *pair;
    char *key;
    int start;

    pair = NULL;
    key = NULL;
    start = 0;
    if (command[(*i)] == '$' && command[(*i) + 1] != ' ')
    {
        if ((command[(*i) + 1] == '\'' || command[(*i) + 1] == '\'') && !check_double(command, (*i), check_in(command[(*i)])))
            ;
        else
            (*i)++;
        if (ft_isdigit(command[(*i)]) || command[(*i)] == '*')
            (*i)++;
        else if (command[(*i)] == '?')
            return (exit_status(content, i));
        if (ft_isalpha(command[(*i)]))
        {
            start = (*i);
            while (command[start] && command[start] != ' ' && command[start] != '$' && command[start] != '"' && command[start] != '\'' && command[start] != '\\')
                start++;
            key = gc(start - (*i) + 1, &content->g_collector);
            ft_strlcpy(key, &command[(*i)], start - (*i) + 1 );
            pair = check_if_there(key, &content->env_list);
            (*i) = start;
            if (!pair)
            {
                if ((*flag) == 1)
                {
                    ft_error_exec_two("bash: ", key, ": ambiguous redirect", 2);
                    (*flag) = 0;
                }
                return (NULL);
            }
            return (pair->value);
        }
    }
    return (NULL);
}


char *check_env_var(t_container *content, char *command, int *flag)
{
    int i;
    char *new_command;
    char *curent_part;
    int is_in;
    char qoute;

    i = 0;
    is_in = 0;
    new_command = NULL;
    while (command[i])
    {
        check_in(command[i]);
        if (!is_in && (command[i] == '\'' || command[i] == '"'))
           ( is_in = 1, qoute = command[i]);
        else if (is_in && qoute == command[i])
            is_in = 0;
        if ((!is_in || (is_in && qoute == '"')) && check_double(command, i, qoute))
        {
            curent_part  = expand(content, command, &i, flag);
            if (curent_part)
            {
                new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
            }
            curent_part = expand_telda(command, &i, &content->env_list);
            if (curent_part)
            {
                new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
            }
        }
        new_command = ft_strchr_join(new_command, command[i], &content->g_collector);
        i++;
    }
    return (new_command);
}

