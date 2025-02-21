
#include "../../includes/minishell.h"

void unset_key(char **cmd, t_env **env_list, t_gc **gc)
{
	(void)gc;
	int	i;
	t_env	*temp;

	i = 0;
	temp = NULL;
	while (cmd[i])
	{
		temp = check_if_there(cmd[i], env_list);
		if (temp != NULL)
			delete_node(env_list, temp->key);
		i++;
	}
}
void handle_unset(char **cmd, t_env **env_list, t_gc **gc)
{
	(void)gc;
    int i  = 0;
    while (cmd[i])
        i++;
    if (i >= 2)
     unset_key(cmd + 1, env_list, gc);
}
