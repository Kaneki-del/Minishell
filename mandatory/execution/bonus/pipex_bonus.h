/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:07 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/14 21:28:03 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 47

typedef struct s_list {
  char **cmd;
  char **redirect;
  int in_fd;
  int out_fd;

} t_list;

char *ft_substr(char const *s, unsigned int start, size_t len);
char **ft_split(const char *s, char c);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char const *s1, char const *s2, char c);
char *ft_substr(char const *s, unsigned int start, size_t len);
char **remove_slach(char *cmd);
void free_commands(char **commands);
char *check_cmd_path(char **path_list, char *cmd_name);
char	*find_executable_path(char **env, char **cmd_tabs);
char *get_env_path(char **env);
char *get_next_line(int fd);
void ft_putstr_fd(char *s, int fd, char c);
int open_file(char *file, int in_or_out);
void	executing(char **env, char **cmd_args);
int get_doc(char **av);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void print_error(char *cmd_input);
void single_command(t_list *list, char **env);

#endif
