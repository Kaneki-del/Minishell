#include "../../includes/minishell.h"

static void intial(t_data **list) {
    t_data *current = *list;

    while (current) {
        current->in_fd = 0;
        current->out_fd = 0;
        current = current->next;  
    }
}

int execute_package(t_data **list,t_gc **g_collector, t_env **env_list)
{
  int list_size;
  int exit_code;

  exit_code = 0;
  if (!list && !*list)
    return (EXIT_FAILURE); // check here 
  list_size = ft_lstsize(*list);
  intial(list);
  if (list_size == 1) {
    get_fds(*list);
    exit_code = single_command(*list, g_collector, env_list);
  } 
  /* else if (list_size >= 2) { */
  /*   exit_code = run_multiple(list, env, g_collector); */
  /* } */
  return (exit_code);
}
