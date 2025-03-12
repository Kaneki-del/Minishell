#include "../../includes/minishell.h"

char *expand_here_doc_lines(t_container *content, char *command)
{
   	int i;
    char *new_command;
    char *curent_part;

    if (!command)
        return (NULL);
    i = 0;
    new_command = NULL;
    curent_part = NULL;
    while (command[i])
    {
        if (command[i] == '$' && (ft_isalnum(command[i + 1]) || command[i + 1] == '?' || command[i + 1] == '_'))
        {
			i++;
			if (command[i] == '?')
			{
				i++;
				new_command = ft_strjoin(new_command, ft_itoa(content->status, &content->g_collector), &content->g_collector);
				continue;
			}
			else if (((ft_isdigit(command[i]) || (!ft_isalpha(command[i]) && command[i] != '_'))))
				i++;
			else if (ft_isalnum(command[i]) || command[i] == '_')
			{
				curent_part = expand(content, command, &i, 0);
				if (curent_part)
				{
					new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
				}
				continue;
			}
        }
        new_command = ft_strchr_join(new_command, command[i], &content->g_collector);
        i++;
    }
    return (new_command);
}
