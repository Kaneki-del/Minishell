#include "../../includes/minishell.h"
#include <stdlib.h>

char	*ft_strdop(const char *s1)
{
	char	*s2;
	char	*original;
	size_t	s1_lent;

	s1_lent = ft_strlen(s1);
	s2 = (char *)malloc(s1_lent + 1);
	if (s2 == NULL)
		return (NULL);
	original = s2;
	while (*s1)
		*(s2++) = *(s1++);
	*s2 = '\0';
	return (original);
}
char	*ft_sobstr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdop(""));
	i = 0;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
#include <string.h>
 t_env *lstnew_env(char *key, char *value){
   t_env *new_node; 

 new_node = (t_env *)malloc(sizeof(t_env)); 
 if (!new_node) 
    return (NULL); 
   new_node->key = strdup(key);
  if (value)
    new_node->value = strdup(value); 
  else 
    new_node->value = NULL;
  new_node->next = NULL; 
   return (new_node); 
} 

char **ft_split_equal_to(const char *s) {
  if (s == NULL)
    return NULL;

  char **str =
      (char **)malloc(sizeof(char *) * 3); // Two substrings + NULL terminator
  if (str == NULL)
    return NULL;

  size_t len = ft_strlen(s);
  size_t j = 0;

  // Find the first '=' or end of string
  while (s[j] != '=' && s[j] != '\0')
    j++;

  // If '=' is found, split key and value
  if (s[j] == '=') {
    str[0] = ft_sobstr(s, 0, j);           // Copy key
    str[1] = ft_sobstr(s, j + 1, len - j); // Copy value
  } else {
    str[0] = ft_strdop(s); // No '=', just copy the entire string as key
    str[1] = NULL;         // No value, set the second part to NULL
  }

  str[2] = NULL; // Null-terminate the array
  return str;
}

void lstadd_back_env(t_env **lst, t_env *new_t) {
  t_env *ptr;
  
  t_env *current = *lst;
  if (!lst || !new_t){
    return;
  }
  else if (*lst == NULL)
    *lst = new_t;
  else {
    ptr = ft_lstlast(current);
    ptr->next = new_t;
  }
}
void clean_pwd(t_env **env_list) {
  t_env *current = NULL;
  current = *env_list;
  while (current) {
    if (ft_strcmp(current->key, "OLDPWD") == 0) {
      free(current->value);
      current->value = NULL;
    }
    current = current->next;
  }
}
// function to copy a local of the env in a linked list
t_env *get_env_list(char **env) 
{
  int i;
  
  i = 0;
  t_env *returned_env;
  returned_env = NULL;
  char **temp;
  while (env[i]) {
    temp = ft_split_equal_to(env[i]);
    lstadd_back_env(&returned_env, lstnew_env(temp[0], temp[1]));
    free(temp);
    i++;
  }
    if (check_if_there("OLDPWD", &returned_env) == NULL)
      lstadd_back_env(&returned_env, lstnew_env("OLDPWD", NULL));
    else  
      clean_pwd(&returned_env);
  return returned_env;
}

