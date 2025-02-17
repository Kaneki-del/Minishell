#include "../../includes/minishell.h"

void single_command(t_data *list, t_env *env_list) {

  pid_t pid;
  if (check_builtin_commands(list->cmds)) {
    built_in(list->cmds, env_list);
    return;
  }
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
    executing(env_list, list->cmds);
  } else {
    int status;
    waitpid(pid, &status, 0); // Wait for the child process to finish
    if (list->in_fd != 0)
      close(list->in_fd);
    if (list->out_fd != 0)
      close(list->in_fd);
  }
}
