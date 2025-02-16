/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:42:19 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/16 20:30:53 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include "./parsing.h"
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_direction {
  char *infd;
  int type_in;
  int type_out;
  char *outfd;
  int err;
} t_direction;

typedef struct s_data {
  char **cmds;
  char **directions;
  int in_fd;
  int out_fd;
  t_type_token dir_input_type;
  t_type_token dir_output_type;
  struct s_data *next;
  int type;
} t_data;

char *ft_strrchr(const char *s, int c);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char *s1, char *s2);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
char *ft_substr(char const *s, unsigned int start, size_t len);
t_data *new_data_node(char **command, char **directions);
void add_data_back(t_data **lst, t_data *new);
char *ft_chrjoin(char c, char b);
void single_command(t_data *list, char **env);
int ft_lstsize(t_data *lst);
void get_fds(t_data *list);
int run_multiple(t_data **list, char **env);
void execute_package(t_data **list, char **env);

void free_commands(char **commands);
char *check_cmd_path(char **path_list, char *cmd_name);
char *find_executable_path(char **env, char **cmd_tabs);
char *get_env_path(char **env);
void ft_putstr_fd(char *s, int fd, char c);
int open_file(char *file, int in_or_out);
void executing(char **env, char **cmd_args);
void print_error(char *cmd_input);

#endif
