/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:42:19 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/21 10:15:22 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef enum s_type_token {
  T_WORD,
  T_PIPE,
  T_REDIRECTE_IN,
  T_REDIRECTE_OUT,
  T_REDIRECTE_APPEND,
  T_REDIRECTE_HEREDOC,
} t_type_token;

typedef struct s_token {
  char *value;
  int index;
  t_type_token token_type;
  struct s_token *next;
} t_token;

typedef struct s_direction {
  char *infd;
  int type_in;
  int type_out;
  char *outfd;
  int err;
} t_direction;

typedef struct s_data {
  char *line;
  char **cmds;
  char **directions;
  int in_fd;
  int out_fd;
  t_type_token dir_input_type;
  t_type_token dir_output_type;
  struct s_data *next;
  int type;
} t_data;

typedef struct s_gc {
  void *adress;
  struct s_gc *next;
} t_gc;

//the env  list struct
typedef struct s_env {
  char *key;
  char *value;
  struct s_env *next;
} t_env;

char *ft_strrchr(const char *s, int c);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1, t_gc **g_collector);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2, t_gc **gc);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
char *ft_substr(char const *s, unsigned int start, size_t len, t_gc **g_collector);
t_data *new_data_node(char **command, char **directions, t_gc **g_collector);
void add_data_back(t_data **lst, t_data *new);
char *ft_chrjoin(char c, char b, t_gc **g_collector);
int single_command(t_data *list, t_gc **g_collector, t_env *env_list);
int ft_lstsize(t_data *lst);
void get_fds(t_data *list);
int run_multiple(t_data **list, char **env, t_gc **g_collector);
int execute_package(t_data **list,t_gc **g_collector, t_env *env_list);
char **ft_split(char const *s, char c, t_gc **g_collector);
t_token *ft_lstnew(char *content, t_type_token type, t_gc **g_collector);
void ft_lstadd_back(t_token **lst, t_token *new);
void *gc(size_t size, t_gc **garbage_list);
void ft_error(char *msg, char dis,int fd, t_gc **g_collector);
void clear_bin(t_gc **garbage_list);
t_env *copy_list(t_env *head);

char *check_cmd_path(char **path_list, char *cmd_name, t_gc **g_collector);
char *find_executable_path(t_env *env_list, char **cmd_tabs, t_gc **gc);
char *get_env_path(t_env *env_list, t_gc **gc);
void ft_putstr_fd(char *s, int fd, char c);
int open_file(char *file, int in_or_out);
void executing(t_env *env_list, char **cmd_args, t_gc **gc) ;
void print_error(char *cmd_input);
t_env *get_env_list(char **env);
int ft_strcmp(const char *s1, const char *s2);
int check_builtin_commands(char **commands);
int built_in(char **cmd, t_env *env_list, t_gc **gc);
t_env *lstnew_env(char *key, char *value);
void print_env_list(t_env *env_list);
char	*ft_strjoin(char const *s1, char const *s2, t_gc **gc);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void print_export(t_env *env_list);
int add_export(char **cmd, t_env **env_list, t_gc **gc);
void lstadd_back_env(t_env **lst, t_env *new);
t_env *ft_lstlast(t_env *lst);
#endif
