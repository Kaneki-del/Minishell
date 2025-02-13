/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:42:19 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/13 15:54:42 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./parsing.h"

typedef struct s_direction
{
    char *infd;
    int type_in;
    int type_out;
    char *outfd;
    int err;
} t_direction;

typedef struct s_data
{
    char **cmds;
    char **directions;
    t_type_token dir_input_type;
    t_type_token dir_output_type;
    struct  s_data *next;
    int type;
} t_data;

char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_data  *new_data_node(char **command, char **directions, t_type_token dir_input_type, t_type_token dir_output_type);
void	add_data_back(t_data **lst, t_data *new);

# endif
