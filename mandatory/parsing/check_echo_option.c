#include "../../includes/minishell.h"

int get_cmds_length(char **cmds)
{
    int i;

    i = 0;
    while (cmds[i])
        i++;
    return (i);
}

char **remove_repeated(char **cmd, t_gc **g_collector)
{
    int i;
    int check;
    int second_check;
    char **new_cmds;
    int j;

    i = 1;
    j = 1;
    second_check = 0;
    check = 0;
    new_cmds = gc(sizeof(char *) * get_cmds_length(cmd), g_collector);
    if (!new_cmds)
        return (NULL);
    new_cmds[0] = cmd[0];
    while (cmd[i])
    {
        if (ft_strcmp(cmd[i], "-n") == 0 && check == 0)
        {
            if (second_check == 0)
                check = 1;
            else
                check = 0;
            new_cmds[j++] = cmd[i++];
            continue ;
        }
        else if(ft_strcmp(cmd[i], "-n") != 0)
        {
            second_check = 1;
            check = 0;
            new_cmds[j] = cmd[i];
            j++;
        }
        i++;
    }
    new_cmds[j] = NULL;
    return (new_cmds);
}

char **check_echo_options(char **cmd, t_gc **g_collector)
{
    int i;
    int j;
   

    i = 1;

    if (!cmd || !cmd[0])
        return (NULL);
    if (ft_strcmp(cmd[0], "echo") != 0)
        return (cmd);
    while (cmd[i])
    {
        if (cmd[i][0] == '-' && cmd[i][1] != '\0')
        {
            j = 1;
            while (cmd[i][j] == 'n')
                j++;
            if (cmd[i][j] == '\0')
                cmd[i] = ft_strdup("-n", g_collector);
            else
                break ;
        }
        i++;
    }
    return (remove_repeated(cmd, g_collector));
}