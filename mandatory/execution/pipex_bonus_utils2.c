/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/17 23:54:07 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>

char **env_to_array(t_env *head) {
  t_env *temp = NULL;
  int count = 0;
  temp = head;
  while (temp) {
    count++;
    temp = temp->next;
  }
  char **env_array = malloc((count + 1) * sizeof(char *));
  if (!env_array) {
    perror("malloc failed");
    exit(1);
  }
  temp = head;
  int i = 0;
  while (temp) {
    // Allocate memory for the concatenated key=value string
    size_t len =
        strlen(temp->key) + strlen(temp->value) + 2; // +2 for '=' and '\0'
    env_array[i] = malloc(len * sizeof(char));
    if (!env_array[i]) {
      perror("malloc failed");
      exit(1);
    }

    // Create the key=value string
    snprintf(env_array[i], len, "%s=%s", temp->key, temp->value);

    temp = temp->next;
    i++;
  }

  env_array[i] = NULL; // Null-terminate the array
  return env_array;
}

void print_error(char *cmd_input) {
  ft_putstr_fd("zsh: command not found: ", 2, 's');
  ft_putstr_fd(cmd_input, 2, 'n');
  exit(127);
}

void executing(t_env *env_list, char **cmd_args) {
  char *cmd_path;

  if (!env_list)
    exit(127);
  if (!cmd_args || !cmd_args[0]) // Check if command is NULL
  {
    print_error("Empty command");
    exit(127);
  }
  cmd_path = find_executable_path(env_list, cmd_args);
  char **list_char = env_to_array(env_list);
  if (cmd_args) {
    if (execve(cmd_path, cmd_args, list_char) == -1) {
      print_error(cmd_args[0]);
      exit(127);
    }
  }

  exit(127);
}
