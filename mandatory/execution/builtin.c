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
// void prtin_tabs(char **cmd)
// {
//   int i = 0;
//   printf("cmd=>|%s|\n", cmd[i]);
//   i++;
// }
void handle_export(char **cmd, t_env **env_list, t_gc **gc) {
  int i = 0;
  while (cmd[i])
    i++;
  if (i == 1)
    print_export(*env_list);
  else if (i >= 2)
    add_export(cmd + 1, env_list, gc);
}

int built_in(char **cmd, t_env **env_list, t_gc **gc) 
{
  // prtin_tabs(cmd);
  if (ft_strcmp(cmd[0], "env") == 0) {
    print_env_list(*env_list);
    return 0;
  } 
  else if (ft_strcmp(cmd[0], "export") == 0) {
    handle_export(cmd, env_list, gc);
    return 0;
  }
  else if (ft_strcmp(cmd[0], "unset") == 0) {
    handle_unset(cmd, env_list, gc);
    return 0;
  }
  else if (ft_strcmp(cmd[0], "echo") == 0) {
  
    handle_echo(cmd,gc);
    return 0;
  }
   else if (ft_strcmp(cmd[0], "pwd") == 0) {
    handle_pwd();
    return 0;
   }
  else if (ft_strcmp(cmd[0], "cd") == 0) {
    handle_cd(cmd + 1, env_list, gc);
    return 0;
   }
  return 1;
   
}
