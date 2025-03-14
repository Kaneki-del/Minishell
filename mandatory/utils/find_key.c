#include "../../includes/minishell.h"
t_env	*check_if_there(const char *key, t_env **env_list)
{
	t_env	*temp;

	temp = NULL;
	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}