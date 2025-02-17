#include "../../includes/minishell.h"
static void intial(t_data **list) {
  t_data *current = NULL;
  current = *list;

  while (current) {
    current->in_fd = 0;
    current->out_fd = 0;
    current = current->next;
  }
}

int execute_package(t_data **list, char **env) {
  int list_size = ft_lstsize(*list);
  int exit_code;
  exit_code = 0;
  intial(list);
  if (list_size == 1) {
    get_fds(*list);
    single_command(*list, env);
  } else if (list_size >= 2) {
    exit_code = run_multiple(list, env);
  }
  return (exit_code);
}
