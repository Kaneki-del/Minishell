/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:39:16 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/16 18:51:57 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_env_path(char **env) {
  int i;
  char *path_value;
  char *env_path;

  i = 0;
  while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
    i++;
  if (!env[i])
    return (NULL);
  env_path = env[i];
  path_value = ft_substr(env_path, 5, ft_strlen(env_path));
  return (path_value);
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

char *find_executable_path(char **env, char **cmd_tabs) {
  char **path_list;
  char *path_value;
  char *cmd_v;

  if (!env)
    return (NULL);
  if (!cmd_tabs || !cmd_tabs[0])
    return ( NULL);
  cmd_v = try_direct_access(cmd_tabs);
  if (cmd_v)
    return (cmd_v);
  path_value = get_env_path(env);
  if (!path_value)
    return (NULL);
  path_list = ft_split(path_value, ':');

  if (!path_list)
    return (NULL);
  cmd_v = check_cmd_path(path_list, cmd_tabs[0]);
  return (cmd_v);
}
