#include "../../includes/minishell.h"

static size_t	w_count(const char *s, char c)
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

static void	mem_free(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static char	*fill(char *p, const char *s, size_t i, size_t len_chrs)
{
	size_t	k;

	k = 0;
	while (k < len_chrs)
	{
		p[k] = s[i + k];
		k++;
	}
	p[k] = '\0';
	return (p);
}

static char	*store_next_word(const char *s, size_t *i, char c)
{
	char	*p;
	size_t	char_count;

	char_count = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	while (s[*i + char_count] && s[*i + char_count] != c)
		char_count++;
	p = (char *)malloc(char_count + 1);
	if (!p)
		return (NULL);
	fill(p, s, *i, char_count);
	*i += char_count;
	return (p);
}

char	**normal_ft_split(char const *s, char c)
{
	char	**p;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	p = malloc((w_count(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while ((w_count(s, c)) > j)
	{
		p[j] = store_next_word(s, &i, c);
		if (!(p[j]))
		{
			mem_free(p);
			return (NULL);
		}
		j++;
	}
	p[j] = NULL;
	return (p);
}