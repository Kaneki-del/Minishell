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
t_env *lstnew_env(char *key, char *value) {
  t_env *new_node;

  new_node = (t_env *)malloc(sizeof(t_env));
  if (!new_node)
    return (NULL);
  new_node->key = key;
  new_node->value = value;
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
t_env *ft_lstlast(t_env *lst) {
  t_env *ptr;

  ptr = lst;
  if (!lst)
    return (NULL);
  while (ptr->next)
    ptr = ptr->next;
  return (ptr);
}
/* int ft_strcmp(const char *s1, const char *s2) { */
/*   size_t i; */
/**/
/*   i = 0; */
/*   if (ft_strlen(s1) != ft_strlen(s2)) */
/*     return 1; */
/*   while ((s1[i] || s2[i])) { */
/*     if ((unsigned char)s1[i] != (unsigned char)s2[i]) */
/*       return ((unsigned char)s1[i] - (unsigned char)s2[i]); */
/*     i++; */
/*   } */
/*   return (0); */
/* } */
void lstadd_back_env(t_env **lst, t_env *new) {
  t_env *ptr;

  if (!lst || !new)
    return;
  else if (*lst == NULL)
    *lst = new;
  else {
    ptr = ft_lstlast(*lst);
    ptr->next = new;
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
  int i = 0;
  t_env *returned_env;
  returned_env = NULL;
  char **temp;
  while (env[i]) {
    temp = ft_split_equal_to(env[i]);
    lstadd_back_env(&returned_env, lstnew_env(temp[0], temp[1]));
    free(temp);
    i++;
  }
  clean_pwd(&returned_env);
  return returned_env;
}
