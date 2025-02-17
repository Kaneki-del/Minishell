#include "../../includes/minishell.h"

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
    str[0] = ft_substr(s, 0, j);           // Copy key
    str[1] = ft_substr(s, j + 1, len - j); // Copy value
  } else {
    str[0] = ft_strdup(s); // No '=', just copy the entire string as key
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

t_env *get_env_list(char **env) {
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
  return returned_env;
}
