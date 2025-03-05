#include "../../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	word_counter(const char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	is_in;

	i = 0;
	count = 0;
	is_in = 0;
	while (s[i])
	{
		if (s[i] != c && is_in == 0)
		{
			count++;
			is_in = 1;
		}
		else if (s[i] == c)
			is_in = 0;
		i++;
	}
	return (count);
}
