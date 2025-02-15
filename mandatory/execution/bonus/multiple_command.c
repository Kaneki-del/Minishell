#include <stdio.h>
#include "pipex_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_first(t_list *list, int *p_fd, char **env) {
  pid_t pid = fork();
  if (pid < 0)
    exit(1);
  if (pid == 0) {
    close(p_fd[0]); // Close unused read end
    if (list->out_fd == 0)
      list->out_fd = p_fd[1];
    else
      close(p_fd[1]); // Close write end if already set

    if (dup2(list->in_fd, 0) < 0) {
      perror("dup2 in_fd");
      exit(1);
    }
    if (dup2(list->out_fd, 1) < 0) {
      perror("dup2 out_fd");
      exit(1);
    }
    executing(env, list->cmd);
  }
  close(p_fd[1]); // Close write end in parent
}

int execute_last(t_list *list, int *p_fd, char **env) {
  pid_t pid = fork();
  if (pid < 0)
    exit(1);
  if (pid == 0) {
    close(p_fd[1]); // Close unused write end
    if (list->out_fd == 0)
      list->out_fd = 1;
    if (list->in_fd == 0)
      list->in_fd = p_fd[0];
    else
      close(p_fd[0]); // Close read end if already set

    if (dup2(list->in_fd, 0) < 0) {
      perror("dup2 in_fd");
      exit(1);
    }
    if (dup2(list->out_fd, 1) < 0) {
      perror("dup2 out_fd");
      exit(1);
    }
    executing(env, list->cmd);
  }
  close(p_fd[0]); // Close read end in parent
  return pid;
}

static void execut(t_list *list, int *p_fd, char **env, int in) {
  pid_t pid = fork();
  if (pid < 0)
    exit(1);
  if (pid == 0) {
    close(p_fd[0]); // Close unused read end
    if (list->out_fd == 0)
      list->out_fd = p_fd[1];
    else
      close(p_fd[1]); // Close write end if already set

    if (list->in_fd == 0)
      list->in_fd = in;
    else
      close(in); // Close previous pipe input

    if (dup2(list->in_fd, 0) < 0) {
      perror("dup2 in_fd");
      exit(1);
    }
    if (dup2(list->out_fd, 1) < 0) {
      perror("dup2 out_fd");
      exit(1);
    }
    executing(env, list->cmd);
  }
  close(p_fd[1]); // Close write end in parent
  close(in); // Close previous pipe input in parent
}

static int handle_pipes(t_list **list, char **env) {
  int p_fd[2];
  t_list *current = *list;

  if (pipe(p_fd) == -1)
    exit(1);
  
  execute_first(current, p_fd, env);
  current = current->next;

  while (current != NULL && current->next != NULL) {
    int t = p_fd[0]; // Save previous pipe read end
    if (pipe(p_fd) == -1)
      exit(1);
    
    get_fds(current);
    execut(current, p_fd, env, t);
    close(t); // Close previous read end in parent
    current = current->next;
  }

  close(p_fd[1]); // Close last write end
  get_fds(current);
  return execute_last(current, p_fd, env);

}

int run_multiple(t_list **list, char **env) {
  int status = 0;
  int exit_code = 0;
  int id_last_command = handle_pipes(list, env);
  waitpid(id_last_command, &status, 0);
  if (WIFEXITED(status)) {
    exit_code = WEXITSTATUS(status);
  }

  while (wait(NULL) > 0); // Wait for all remaining child processes
  return exit_code;
}
