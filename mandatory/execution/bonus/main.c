#include "pipex_bonus.h"
#include <stdio.h>

int main(int argc, char *argv[], char **env) {
  (void)argc;
  (void)argv;
  t_list *list = NULL;
  list = malloc(sizeof(t_list));
  t_list *list2 = malloc(sizeof(t_list));
  t_list *list3 = malloc(sizeof(t_list));
  list->cmd = NULL;
  list->redirect = NULL;
  list->redirect = ft_split(" < in < /dev/stdin  ", ' ');
  list->cmd = ft_split("cat ", ' ');
  list->next = list2;

  list2->cmd = NULL;
  list2->redirect = NULL;
  list2->redirect = ft_split("  file", ' ');
  list2->cmd = ft_split("ls", ' ');
  list2->next = NULL;

  list3->redirect = ft_split("  > /dev/stdout", ' ');
  list3->cmd = ft_split("ls ", ' ');
  list3->next = NULL;
  list->in_fd = 0;
  list->in_fd = 0;
  list2->in_fd = 0;
  list2->out_fd = 0;
  list3->out_fd = 0;
  list3->out_fd = 0;

  int list_size = ft_lstsize(list);
  int exit_code;
  if (list_size == 1) {
    get_fds(list);
    single_command(list, env);
  } else if (list_size >= 2) {
    exit_code = run_multiple(&list, env);
  }
  exit(exit_code);
}
