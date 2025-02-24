
#include "../../includes/minishell.h"
int check_builtin_commands(char **commands) {
  // List of built-in commands
  char *builtins[] = {"cd", "pwd", "export", "unset", "env", "exit", "echo"};

  // Check if the first command (index 0) matches any built-in command
  if (commands[0] != NULL) 
  {
    if (ft_strcmp(commands[0], builtins[0]) == 0 ||
        ft_strcmp(commands[0], builtins[1]) == 0 ||
        ft_strcmp(commands[0], builtins[2]) == 0 ||
        ft_strcmp(commands[0], builtins[3]) == 0 ||
        ft_strcmp(commands[0], builtins[4]) == 0 ||
        ft_strcmp(commands[0], builtins[5]) == 0 ||
        ft_strcmp(commands[0], builtins[6]) == 0 )
        {
      return 1;
    }
  } 
  return 0;
}
