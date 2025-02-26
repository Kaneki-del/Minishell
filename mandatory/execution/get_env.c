#include "../../includes/minishell.h"



t_env	*lstnew_env(char *key, char *value, t_gc **g_env_collector)
{
	t_env	*new_node;

	new_node = (t_env *)gc(sizeof(t_env), g_env_collector);
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key, g_env_collector);
	if (value)
		new_node->value = ft_strdup(value, g_env_collector);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

char **ft_split_equal_to(const char *s, t_gc **g_collector) 
{
  char **str;
  size_t len;
  size_t j;

  if (s == NULL)
    return NULL;
  str =
      gc(sizeof(char *) * 3, g_collector); // Two substrings + NULL terminator
  if (str == NULL)
    return NULL;
  len = ft_strlen(s);
  j = 0;
  // Find the first '=' or end of string
  while (s[j] != '=' && s[j] != '\0')
    j++;

  // If '=' is found, split key and value
  if (s[j] == '=') 
  {
    str[0] = ft_substr(s, 0, j, g_collector);           // Copy key
    str[1] = ft_substr(s, j + 1, len - j, g_collector); // Copy value
  } 
  else 
  {
    str[0] = ft_strdup(s, g_collector); // No '=', just copy the entire string as key
    str[1] = NULL;         // No value, set the second part to NULL
  }
  str[2] = NULL; // Null-terminate the array
  return str;
}

void	lstadd_back_env(t_env **lst, t_env *new_t)
{
	t_env	*ptr;
	t_env	*current;

	current = *lst;
	if (!lst || !new_t)
	{
		return ;
	}
	else if (*lst == NULL)
		*lst = new_t;
	else
	{
		ptr = ft_lstlast(current);
		ptr->next = new_t;
	}
}
void	clean_pwd(t_env **env_list)
{
	t_env	*current;

	current = NULL;
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
			current->value = NULL;
		current = current->next;
	}
}
// function to copy a local of the env in a linked list
t_env	*get_env_list(char **env, t_container *content)
{
	int		i;
	t_env	*returned_env;
	char	**temp;

	i = 0;
	returned_env = NULL;
	while (env[i])
	{
		temp = ft_split_equal_to(env[i], &content->g_collector);
		lstadd_back_env(&returned_env, lstnew_env(temp[0], temp[1], &content->g_env_collector) );
		i++;
	}
	if (check_if_there("OLDPWD", &returned_env) == NULL)
		lstadd_back_env(&returned_env, lstnew_env("OLDPWD", NULL, &content->g_env_collector));
	else
		clean_pwd(&returned_env);
	return (returned_env);
}
