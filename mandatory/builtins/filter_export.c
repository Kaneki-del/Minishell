
#include "../../includes/minishell.h"
t_env *ft_lstlast(t_env *lst) {
  t_env *ptr;

  ptr = lst;
  if (!lst)
    return (NULL);
  while (ptr->next)
    ptr = ptr->next;
  return (ptr);
}
// void lstadd_back_env(t_env **lst, t_env *new) {
//   t_env *ptr;

//   if (!lst || !new)
//     return;
//   else if (*lst == NULL)
//     *lst = new;
//   else {
//     ptr = ft_lstlast(*lst);
//     ptr->next = new;
//   }
// }
int filter_key(char *key, char *value)
{
  int i = 0;
  int j = 0;
  if (key[0] >= '0' && key[0] <= '9')
    return 1;
  while (key[j])
    j++;
  while (key[i])
  {
    if (!((key[i] >= 'a' && key[i] <= 'z') || 
          (key[i] >= 'A' && key[i] <= 'Z') || 
          (key[i] >= '0' && key[i] <= '9') ||
          key[i] == '_' ||
          (i == j - 1 && key[i] == '+' && value != NULL))) // Only allow '+' at the end
      return 1; // Invalid key, return immediately
    i++; // Increment only if the character is valid
  }
  return 0;
}
t_env *check_if_there(char *key, t_env **env_list)
{
  t_env *temp = NULL;
  temp = *env_list;
  while (temp)
  {
    if (ft_strcmp(key, temp->key) == 0)
      return temp;
    temp = temp->next;
  }
  return NULL;
}
void do_mode(char **key_value, t_env **node, t_gc **gc)
{
  char *key = NULL;
  char *value = NULL;
  key = key_value[0];
  value = key_value[1]; 
  if (key[ft_strlen(key) -1] == '+')
    (*node)->value = ft_strjoin((*node)->value, value, gc);
  else
    (*node)->value = value;
}
char **get_befor(const char *cmd, t_gc **gc) {
  int i = 0;
  char **to_return = (char **)malloc(sizeof(char *) * 3);

  while (cmd[i] != '=' && cmd[i])
    i++;
  to_return[0] = ft_substr(cmd, 0, i, gc);
  if (cmd[i] == '=') {
    i++;
    to_return[1] = ft_substr(cmd + i, i, ft_strlen(cmd + i), gc);
  } else
    to_return[1] = NULL;
  to_return[3] = 0;
  return to_return;
}
int add_export(char **cmd, t_env **env_list, t_gc **gc)
{
  int i = 0;
  char **splited_equal;
  int status;
  t_env *temp = NULL;
  while (cmd[i]) {
    splited_equal = get_befor(cmd[i], gc);
    if (filter_key(cmd[0], cmd[1]) == 0)
    {
      temp = check_if_there(cmd[0], env_list) ;
      if (temp != NULL)
        do_mode(cmd, &temp, gc);
      else
        lstadd_back_env(env_list, lstnew_env(splited_equal[0], splited_equal[1]));
    }
    else{
      printf("not valid");
      status = 1;
    }
    i++;
  }
  return status;
}
