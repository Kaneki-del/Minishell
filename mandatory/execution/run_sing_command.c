#include "../../includes/minishell.h"
void print_er(char **str)
{
  int i = 0;
  while (str[i])
  {
    printf("->%s\n",str[i]);
    i++;
  }
}
int single_command(t_data *list, t_gc **g_collector, t_env **env_list, t_gc **gc_env) 
{
    pid_t pid;
    int status = 0;
    // print_er(list->cmds);
    // printf("__________________\n");
    // if (list->directions)
    //   print_er(list->directions);
    
    if (check_builtin_commands(list->cmds)) {
        return (built_in(list->cmds, env_list, gc_env));
       
    }
    pid = fork();
    if (pid < 0)
        exit(1);

    if (pid == 0) {  // Child process
        if (list->in_fd != 0) 
        {
            if (dup2(list->in_fd, 0) < 0) {
                close(list->in_fd);
                close(list->out_fd);
                exit(1);
            }
            close(list->in_fd);
        }
        if (list->out_fd != 0) {
            if (dup2(list->out_fd, 1) < 0) {
                close(list->out_fd);
                exit(1);
            }
            close(list->out_fd);
        }
        executing(*env_list, list->cmds, g_collector);
    } 
    else {  // Parent process
        if (list->in_fd != 0)
            close(list->in_fd);
        if (list->out_fd != 0)
            close(list->out_fd);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) { 
            return WEXITSTATUS(status); 
        }
    }
    return 1; 
}
