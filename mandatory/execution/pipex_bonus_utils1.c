/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:39:16 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/17 23:27:31 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

char *get_env_path(t_env *env_list) {
  char *env_path;
  t_env *current;
  current = NULL;
  current = env_list;
  env_path = NULL;
  while (current) {
    if (ft_strncmp(current->key, "PATH", ft_strlen(current->key)) == 0) {
      env_path = ft_strdup(current->value);
      if (env_path == NULL)
        return NULL;
    }
    current = current->next;
  }
  return env_path;
}

char *check_cmd_path(char **path_list, char *cmd_name) {
  int i;
  char *full_cmd_path;
  i = 0;
  while (path_list[i]) {
    full_cmd_path = ft_strjoin(path_list[i], "/");
    full_cmd_path = ft_strjoin(full_cmd_path, cmd_name);
    if (!full_cmd_path) {

      return (NULL);
    }
    if (access(full_cmd_path, X_OK) == 0) {

      return (full_cmd_path);
    }

    i++;
  }

  return (NULL);
}

static char *try_direct_access(char **cmd_tabs) {
  char *cmd_v;

  if (access(cmd_tabs[0], X_OK) == 0) {
    cmd_v = ft_strdup(cmd_tabs[0]);
    return (cmd_v);
  }
  return (NULL);
}

char *find_executable_path(t_env *env_list, char **cmd_tabs) {
  char **path_list;
  char *path_value;
  char *cmd_v;

  if (!env_list)
    return (NULL);
  if (!cmd_tabs || !cmd_tabs[0])
    return (NULL);
  cmd_v = try_direct_access(cmd_tabs);
  if (cmd_v)
    return (cmd_v);
  path_value = get_env_path(env_list);
  if (!path_value)
    return (NULL);
  path_list = ft_split(path_value, ':');

  if (!path_list)
    return (NULL);
  cmd_v = check_cmd_path(path_list, cmd_tabs[0]);
  return (cmd_v);
}
