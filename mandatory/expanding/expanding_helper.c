#include "../../includes/minishell.h"

char **filter_all(char **cmds, t_gc **g_collector, t_container *content)
{
    int i;

    i = 0;
    if (!cmds)
        return (NULL);
    while (cmds[i])
    {
        cmds[i] = remove_quotes(cmds[i], g_collector, content);
        i++;
    }
    return (cmds);
}

int get_char_index(char *s, char c)
{
    int i = 0;
    int store = 0;
    char qoute;
    int is_in;

    is_in = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'' )
        {
            if (is_in == 0 )
            {
                is_in = 1;
                qoute = s[i];
            }
            else if (is_in == 1 && qoute == s[i])
                is_in = 0;
        }
        if (s[i] == c && !is_in)
            store = i;
        i++;
    }
    return (store);
}

char *remove_quotes(char *command, t_gc **g_collector ,t_container *content)
{
    char *res;
    int i;
    int j;
    char current_quote;

    current_quote = '\0';
    j = 0;
    i = 0;
    if (!command) 
        return (NULL);
    res = gc(ft_strlen(command) + 1, g_collector, content);
    if (!res) 
        return (NULL);
    while (command[i])
    {
        if (current_quote == '\0' && (command[i] == '\'' || command[i] == '"'))
            current_quote = command[i++];
        else if (current_quote && command[i] == current_quote)
        {
            current_quote = '\0';
            i++;
        }
        else
            res[j++] = command[i++];
    }
    res[j] = '\0';
    return res;
}