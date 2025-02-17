#include "../../includes/minishell.h"
void print_env_list(t_env *env_list) {
  t_env *current = env_list;

  // Traverse the list and print each node's key and value
  while (current != NULL) {
    printf("%s=%s\n", current->key, current->value);
    current = current->next; // Move to the next node
  }
}
int built_in(char **cmd, t_env *env_list) {
  if (ft_strncmp(cmd[0], "env", 3) == 0) {
    print_env_list(env_list);
    return 0;
  }
  return 1;
}
