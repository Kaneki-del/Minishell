#include "../../includes/minishell.h"

char single_qoutes(char c)
{
    static int is_in;
    static char qoute;

    if (c == '\'')
    {
        if (!is_in)
        {
            is_in = 1;
            qoute = c;
        }
        else if (is_in && c == qoute)
        {
            is_in = 0;
            qoute = '\0';
        }
    }
    return (qoute);
}

char double_qoutes(char c)
{
    static int is_in;
    static char qoute;

    if (c == '"')
    {
        if (!is_in)
        {
            is_in = 1;
            qoute = c;
        }
        else if (is_in && c == qoute)
        {
            is_in = 0;
            qoute = '\0';
        }
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
    if (command[(*i)] == '~' && ((command[(*i) + 1] == ' ' || command[(*i) + 1] == '\0' || command[(*i) + 1] == '/') && (command[(*i) - 1] == ' ' || command[0] == '~' || ft_strncmp(command, "export ", 7) == 0)))
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
    // char qoute;

    pair = NULL;
    key = NULL;
    start = (*i);
    content->is_expandable = 1;
    while (command[start] && ft_isalnum(command[start]))
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
        return (ft_strdup("\0", &content->g_collector));
    }
    return (pair->value);
}

// the first this is the epandable string shoud starts with $ and end with special character 
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
    curent_part = NULL;
    if (!command)
        return (NULL);
    while (command[i])
    {
        if (command[i] == '\'' || command[i] == '"')
        {
            if (!is_in)
            {
                is_in = 1;
                qoute = command[i];
            }
            else if (is_in && command[i] == qoute)
            {
                is_in = 0;
                qoute = '\0';
            }
        }
        if (command[i] == '$' && qoute != '\'' && command[i + 1] != qoute && command[i + 1] != '\0')
        {
            if (command[i] && qoute == '"' && command[i + 1] == '\'')
                ;
            else
            {
                i++;
                if (!ft_isalpha(command[i]) || qoute == '"')
                    (*flag) = 3;
                if (command[i] == '?')
                    new_command = ft_strjoin(new_command, exit_status(content, &i), &content->g_collector);
                else if (ft_isdigit(command[i]) || !ft_isalpha(command[i]))
                    i++;
                else if (ft_isalnum(command[i]))
                {
                    curent_part = expand(content, command, &i, flag);
                    if (curent_part)
                        new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
                    continue;
                }
            }
        }
        else if(qoute != '"' && qoute != '\'' && command[i] == '~')
        {
                curent_part = expand_telda(command, &i, &content->env_list);
                if (curent_part)
                    new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
        }
        new_command = ft_strchr_join(new_command, command[i], &content->g_collector);
        i++;
    }
    return (new_command);
}

