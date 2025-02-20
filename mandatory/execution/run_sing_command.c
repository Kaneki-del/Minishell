#include "../../includes/minishell.h"

void single_command(t_data *list, char **env, t_gc **g_collector) {

  pid_t pid;
  pid = fork();
  if (pid < 0)
    exit(1);
  if (pid == 0) {
    if (list->in_fd != 0) {
      list->in_fd = 0;
      if (dup2(list->in_fd, 0) < 0) {
        close(list->in_fd);
        close(list->out_fd);
        exit(1);
      }
    }
    if (list->out_fd != 0) {
      if (dup2(list->out_fd, 1) < 0) {
        close(list->in_fd);
        close(list->out_fd);
        exit(1);
      }
    }
    if (list->in_fd != 0)
      close(list->in_fd);
    if (list->out_fd != 0)
      close(list->in_fd);
    executing(env, list->cmds, g_collector);
  } else {
    int status;
    waitpid(pid, &status, 0); // Wait for the child process to finish
    if (list->in_fd != 0)
      close(list->in_fd);
    if (list->out_fd != 0)
      close(list->in_fd);
  }
}
