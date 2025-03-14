#include "../../includes/minishell.h"

size_t	ft_strlen_2d(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char in_quotations(char *command, int *i, char qoute, int *is_in)
{
    if (command[(*i)] == '\'' || command[(*i)] == '"')
    {
        if (!*is_in)
        {
            *is_in = 1;
            qoute = command[(*i)];
        }
        else if (*is_in && command[(*i)] == qoute)
        {
            *is_in = 0;
            qoute = '\0';
        }
    }
    return (qoute);
}