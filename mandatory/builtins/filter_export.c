
#include "../../includes/minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

int	filter_key(char *key, char *value)
{
	int	i;

	i = 0;
	if (key[0] >= '0' && key[0] <= '9')
		return ( 1);
	while (key[i] && key[i + 1])
	{
		if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A'
					&& key[i] <= 'Z') || (key[i] >= '0' && key[i] <= '9')
				|| key[i] == '_'))
			return (1); // Invalid key, return immediately
		i++;          // Increment only if the character is valid
	}
	if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] >= '0' && key[i] <= '9') || key[i] == '_'
			|| (key[i] == '+' && value != NULL)))
	{
		return (1);
	}
	return (0);
}
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

void	do_mode(char **key_value, t_env **node, t_gc **g_env_collector, int a)
{
	
	char	*value;

	value = NULL;
	value = key_value[1];
	if (a == 1)
		(*node)->value = ft_strjoin((*node)->value, value, g_env_collector);
	else
	{
		if (value)
			(*node)->value = ft_strdup(value, g_env_collector);
	}
}
char **get_befor(const char *cmd, t_gc **g_collector) 
{
  int i;
  
  i = 0;
  char **to_return = (char **)gc(sizeof(char *) * 3, g_collector);
  while (cmd[i] != '=' && cmd[i])
    i++;
  to_return[0] = ft_substr(cmd, 0, i, g_collector);
  
  if (cmd[i] == '=') 
  {
    i++;
    to_return[1] = ft_substr(cmd , i , ft_strlen(cmd + i), g_collector);
	
  } 
  else
    to_return[1] = NULL;
  to_return[2] = 0;
  return to_return;
}

void valid_key(char **key_value, t_container *content)
{
	int	a;
	t_env *temp;

	a = 0;
	if (key_value[0][ft_strlen(key_value[0]) - 1] == '+')
			{
				key_value[0][ft_strlen(key_value[0]) - 1] = '\0';
				a = 1;
			}
	temp = check_if_there(key_value[0], &content->env_list);\
	if (key_value[0] && ft_strcmp(key_value[0] , "_"))
	{
		if (temp != NULL)
			do_mode(key_value, &temp, &content->g_env_collector, a);
		else
			lstadd_back_env(&content->env_list, lstnew_env(key_value[0], key_value[1], &content->g_env_collector, 0));
	}		
}

int	add_export(char **cmd, t_container *content)
{
	int		i;
	char	**splited_equal;
	int		status;
	

	i = 0;
	status = 0;

	clean_fd(content->data);
	while (cmd[i])
	{
		splited_equal = get_befor(cmd[i], &content->g_collector);
		if (filter_key(splited_equal[0], splited_equal[1]) == 0 && splited_equal[0])
			valid_key(splited_equal, content);
		else{
			ft_error_exec("bash: export:", cmd[i], ": not a valid identifier", 2),
			status = 1;
		}
		i++;
	}
	return (status);
}
