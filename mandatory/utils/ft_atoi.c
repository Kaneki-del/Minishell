#include "../../includes/minishell.h"

int	ft_atoi(const char *str)
{
	ssize_t	result;
	int		signe;

	result = 0;
	signe = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (signe == 1 && result > ((9223372036854775807) - (*str - '0')) / 10)
			return (-1);
		if (signe == -1 && result > ((9223372036854775807) - (*str - '0')) / 10)
			return (0);
		result = (result * 10) + (*(str++) - '0');
	}
	return ((int)(result * signe));
}