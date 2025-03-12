#include "../../includes/minishell.h"

int here_doc_expander(t_container *content, char *command, char **new_command, int *i)
{
    char *curent_part;

    curent_part = NULL;
	(*i)++;
	if (command[(*i)] == '?')
	{
		(*i)++;
		*new_command = ft_strjoin(*new_command, ft_itoa(content->status, &content->g_collector), &content->g_collector);
		return (1);
	}
	else if (((ft_isdigit(command[(*i)]) || (!ft_isalpha(command[(*i)]) && command[(*i)] != '_'))))
		(*i)++;
	else if (ft_isalnum(command[(*i)]) || command[(*i)] == '_')
	{
		curent_part = expand(content, command, i);
		if (curent_part)
			*new_command = ft_strjoin(*new_command, curent_part, &content->g_collector);
		return (1);
	}
	return (0);
}

char *expand_here_doc_lines(t_container *content, char *command)
{
   	int i;
    char *new_command;

    if (!command)
        return (NULL);
    i = 0;
    new_command = NULL;
    while (command[i])
    {
        if (command[i] == '$' && (ft_isalnum(command[i + 1]) || command[i + 1] == '?' || command[i + 1] == '_'))
        {
			if (here_doc_expander(content, command, &new_command, &i) == 1)
				continue;
        }
        new_command = ft_strchr_join(new_command, command[i], &content->g_collector);
        i++;
    }
    return (new_command);
}
