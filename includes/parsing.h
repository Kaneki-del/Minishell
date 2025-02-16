/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:37:24 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/16 18:49:21 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

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

char **ft_split(char const *s, char c);
t_token *ft_lstnew(char *content, t_type_token type);
void ft_lstadd_back(t_token **lst, t_token *new);

#endif
