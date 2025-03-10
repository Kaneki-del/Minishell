
#include "../../includes/minishell.h"

int	filter_unset(char *key)
{
	int	i;

	i = 0;
	if ((key[0] >= '0' && key[0] <= '9') || key[0] == '\0')
		return (1);
	while (key[i] && key[i])
	{
		if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A'
					&& key[i] <= 'Z') || (key[i] >= '0' && key[i] <= '9')
				|| key[i] == '_'))
			return (1); // Invalid key, return immediately
		i++;          // Increment only if the character is valid
	}
	return (0);
}

int	unset_key(char **cmd, t_env **env_list)
{
	int		i;
	t_env	*temp;
	int status;

	i = 0;
	status = 0;
	temp = NULL;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "_"))
		{
			i++;
			continue;
		}
		if (filter_unset(cmd[i]) == 0)
		{
			temp = check_if_there(cmd[i], env_list);
			if (temp != NULL && temp->print_flag == 0)
				delete_node(env_list, temp->key);
		}
		else {
			ft_error_exec("bash: unset:", cmd[i], ": not a valid identifier", 2), 
			status = 1;
		}
		i++;	
	}
	return status;
}
int	handle_unset(char **cmd, t_env **env_list, t_data *current)
{
	int	i;

	clean_fd(current);
	i = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
		return unset_key(cmd + 1, env_list);
	return 0;
}
