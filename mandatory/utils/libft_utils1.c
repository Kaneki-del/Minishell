#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

char	*ft_strrchr(const char *s, int c)
{
	char	conv_char;
	char	*store;

	conv_char = (char)c;
	store = NULL;
	while (*s)
	{
		if (*s == conv_char)
			store = (char *)s;
		s++;
	}
	if (conv_char == '\0')
		return ((char *)s);
	return (store);
}