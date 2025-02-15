#include "pipex_bonus.h"
#include <stdio.h>

static int execut(int fd_in, t_list *list, int *p_fd, char **env) {
  pid_t pid;

  pid = fork();
  if (pid < 0) {
    exit(0);
  }
  if (pid == 0) {

    close(p_fd[0]);
    if (list->out_fd == 0) {
      list->out_fd = p_fd[1];
      if (list->out_fd == 0)
        list->out_fd = 1;
    } else {
      list->out_fd = 1;
      close(p_fd[1]);
    }
    // if note having any in rideraction
    if (fd_in == 0)
      list->in_fd = 0;

    if (dup2(list->in_fd, 0) < 0) {
      printf("erro in dup2");
      exit(1);
    }

    if (dup2(list->out_fd, 1) < 0) {
      printf("erro in dup2");
      exit(1);
    }
    return (executing(env, list->cmd), 1);

  } else {
    return pid;
  }
}

static int handle_pipes(t_list **list, char **env) {
  int p_fd[2];
  int fd[2];

  t_list *current = NULL;
  current = *list;

  while (current != NULL && current->next != NULL &&
         current->next->next != NULL) {
    if (pipe(p_fd) == -1)
      exit(1);
    get_fds(current);
    fd[0] = current->in_fd;  // 0
    fd[1] = current->out_fd; // 0
    execut(current->in_fd, current, p_fd, env);
    close(p_fd[1]);
    current->in_fd = p_fd[0];
  }
  get_fds(current);
  fd[0] = current->in_fd;  // 0
  fd[1] = current->out_fd; // 0
  return execut(p_fd[0], current, fd, env);
}

int run_multiple(t_list **list, char **env) {
  int status;
  status = 0;
  int exit_code;
  int id_last_command = handle_pipes(list, env);
  waitpid(id_last_command, &status, 0);
  if (WIFEXITED(status)) {
    exit_code = WEXITSTATUS(status);
  }
  while (wait(NULL) > 0)
    ;
  return (exit_code);
}
