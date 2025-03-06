#include "../../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str_char;

	i = 0;
	str_char = (unsigned char *)b;
	while (i < len)
		str_char[i++] = (unsigned char)c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (size > SIZE_MAX / count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}