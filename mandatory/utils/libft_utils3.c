#include "../../includes/minishell.h"

size_t	ft_strlen_2d(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}