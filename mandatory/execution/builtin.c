#include "../../includes/minishell.h"
#include <stdio.h>
void print_env_list(t_env *env_list) {
  t_env *current = env_list;

  // Traverse the list and print each node's key and value
  while (current != NULL) {
    if (current->key && current->value)
      printf("%s=%s\n", current->key, current->value);
    current = current->next;
  }
}
/**/
/* char **get_befor(const char *cmd) { */
/*   int i = 0; */
/*   char **to_return = (char **)malloc(sizeof(char *) * 3); */
/**/
/*   while (cmd[i] != '=' && cmd[i]) */
/*     i++; */
/*   to_return[0] = ft_substr(cmd, 0, i); */
/*   if (cmd[i] == '=') { */
/*     i++; */
/*     to_return[1] = ft_substr(cmd + i, i, ft_strlen(cmd + i)); */
/*   } else */
/*     to_return[1] = NULL; */
/*   to_return[3] = 0; */
/*   return to_return; */
/* } */
/* t_env *check_if_there(char *key, t_env **env_list) */
/* { */
/*   t_env *temp = NULL; */
/*   temp = *env_list; */
/*   while (temp) */
/*   { */
/*     if (ft_strcmp(key, temp->key) == 0) */
/*       return temp; */
/*     temp = temp->next; */
/*   } */
/*   return NULL; */
/* } */
/* void do_mode(char **key_value, t_env **node) */
/* { */
/*   char *key = NULL; */
/*   char *value = NULL; */
/*   key = key_value[0]; */
/*   value = key_value[1];  */
/*   if (key[ft_strlen(key) -1] == '+') */
/*     (*node)->value = ft_strjoin((*node)->value, value); */
/*   else */
/*     (*node)->value = value; */
/* } */
/* int add_export(char **cmd, t_env **env_list) { */
/*   int i = 0; */
/*   char **splited_equal; */
/*   int status; */
/*   t_env *temp = NULL; */
/*   while (cmd[i]) { */
/*     splited_equal = get_befor(cmd[i]); */
/*     if (filter_key(cmd[0], cmd[1]) == 0) */
/*     { */
/*       temp = check_if_there(cmd[0], env_list) ; */
/*       if (temp != NULL) */
/*         do_mode(cmd, &temp); */
/*       else */
/*         lstadd_back_env(env_list, lstnew_env(splited_equal[0], splited_equal[1])); */
/*     } */
/*     else{ */
/*       printf("not valid"); */
/*       status = 1; */
/*     } */
/*     i++; */
/*   } */
/*   return status; */
/* } */
/**/
/* void handle_export(char **cmd, t_env *env_list) { */
/*   int i = 0; */
/*   while (cmd[i]) */
/*     i++; */
/*   ; */
/*   if (i == 1) */
/*     print_export(env_list); */
/*   else if (i >= 2) */
/*     add_export(cmd + 1, &env_list); */
/* } */

int built_in(char **cmd, t_env *env_list) {
  if (ft_strcmp(cmd[0], "env") == 0) {
    print_env_list(env_list);
    return 0;
  } 
  /* else if (ft_strcmp(cmd[0], "export") == 0) { */
    /* handle_export(cmd, env_list); */
    /* return 0; */
  /* } */
  return 1;
}
