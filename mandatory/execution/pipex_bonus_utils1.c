/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:39:16 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/20 19:22:11 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

char *get_env_path(t_env *env_list, t_gc **gc) 
{
  char *env_path;
  t_env *current;
  current = NULL;
  current = env_list;
  env_path = NULL;
  while (current) {
    if (ft_strcmp(current->key, "PATH") == 0) {
      env_path = ft_strdup(current->value, gc);
      //to see is the path is catched or not
      printf("the pathis (%s)\n", env_path);
      if (env_path == NULL)
        return NULL;
    }
    current = current->next;
  }
  return env_path;
}

char *check_cmd_path(char **path_list, char *cmd_name, t_gc **gc) {
  int i;
  char *full_cmd_path;
  i = 0;
  while (path_list[i]) {
    full_cmd_path = ft_strjoin(path_list[i], "/", gc);
    full_cmd_path = ft_strjoin(full_cmd_path, cmd_name, gc);
    if (!full_cmd_path) {

      return (NULL);
    }
    if (access(full_cmd_path, X_OK) == 0) {

      printf("the returned path is %s\n", full_cmd_path);
      return (full_cmd_path);
    }

    i++;
  }

  return (NULL);
}

static char *try_direct_access(char **cmd_tabs, t_gc **gc) {
  char *cmd_v;

  if (access(cmd_tabs[0], X_OK) == 0) {
    cmd_v = ft_strdup(cmd_tabs[0], gc);
    return (cmd_v);
  }
  return (NULL);
}

char *find_executable_path(t_env *env_list, char **cmd_tabs, t_gc **gc) {
  char **path_list;
  char *path_value;
  char *cmd_v;

  if (!env_list)
    return (NULL);
  if (!cmd_tabs || !cmd_tabs[0])
    return (NULL);
  cmd_v = try_direct_access(cmd_tabs, gc);
  if (cmd_v)
    return (cmd_v);
  path_value = get_env_path(env_list, gc);
  if (!path_value)
    return (NULL);
  path_list = ft_split(path_value, ':', gc);

  if (!path_list)
    return (NULL);
  cmd_v = check_cmd_path(path_list, cmd_tabs[0], gc);
  return (cmd_v);
}
