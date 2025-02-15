#include "pipex_bonus.h"

int main(int argc, char *argv[], char **env) {
  (void)argc;
  (void)argv;
  t_list *list = NULL;
  list = malloc(sizeof(t_list));
  t_list *list2 = malloc(sizeof(t_list));
  list->cmd = NULL;
  list->redirect = NULL;
  list->in_fd = 0;
  list->out_fd = 0;
  list->redirect = ft_split("  file2", ' ');
  list->cmd = ft_split("ls ", ' ');
  list->next = NULL;

  int list_size = ft_lstsize(list);
  if (list_size == 1) {
    get_fds(list);
    single_command(list, env);
  } else if (list_size >= 2)
    get_fds(list);
  run_multiple(list);
}
