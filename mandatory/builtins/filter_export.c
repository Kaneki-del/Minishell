
#include "../../includes/minishell.h"

t_env *ft_lstlast(t_env *lst) 
{
  t_env *ptr;

  if (!lst)
    return NULL;
  ptr = lst;
  while (ptr->next)  
    ptr = ptr->next;
  return ptr;  
}

int filter_key(char *key, char *value)
{
  int i = 0;

  if (key[0] >= '0' && key[0] <= '9')
    return 1;
 
  while (key[i] && key[i + 1])
  {
    if (!((key[i] >= 'a' && key[i] <= 'z') || 
          (key[i] >= 'A' && key[i] <= 'Z') || 
          (key[i] >= '0' && key[i] <= '9') ||
          key[i] == '_' ))
      return 1; // Invalid key, return immediately
    i++; // Increment only if the character is valid
  }
  if (!((key[i] >= 'a' && key[i] <= 'z') || 
          (key[i] >= 'A' && key[i] <= 'Z') || 
          (key[i] >= '0' && key[i] <= '9') ||
          key[i] == '_'  || (key[i] == '+' && value != NULL ))){
            return 1;
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
#include <string.h>
void do_mode(char **key_value, t_env **node, t_gc **gc, int a)
{
  char *key = NULL;
  char *value = NULL;
  key = key_value[0];
  value = key_value[1];
  if (a == 1)
    (*node)->value = ft_strjoin((*node)->value, value, gc);
  else
    (*node)->value = strdup(value);
}
char **get_befor(const char *cmd, t_gc **gc) 
{
  int i;
  
  i = 0;
  char **to_return = (char **)malloc(sizeof(char *) * 3);
  while (cmd[i] != '=' && cmd[i])
    i++;
  to_return[0] = ft_substr(cmd, 0, i, gc);
  if (cmd[i] == '=') 
  {
    i++;
    to_return[1] = ft_substr(cmd , i , ft_strlen(cmd + i), gc);
  } 
  else
    to_return[1] = NULL;
  to_return[3] = 0;
  return to_return;
}

int add_export(char **cmd, t_env **env_list, t_gc **gc)
{
  int i = 0;
  int a = 0;
  char  **splited_equal;
  int   status;
  t_env *temp = NULL;
  while (cmd[i]) 
  {
    splited_equal = get_befor(cmd[i], gc);
    if (filter_key(splited_equal[0], splited_equal[1]) == 0)
    {
      if (splited_equal[0][ft_strlen(splited_equal[0]) -1] == '+')
      {
        splited_equal[0][ft_strlen(splited_equal[0]) - 1] = '\0';
        a = 1; 
      } 
      temp = check_if_there(splited_equal[0], env_list) ;
      if (temp != NULL)
        do_mode(splited_equal, &temp, gc, a);
      else
      
        lstadd_back_env(env_list, lstnew_env(splited_equal[0], splited_equal[1]));
    }
    else{
      printf("this is not valid\n");
      status = 1;
    }
    i++;
  }
  return status;
}
