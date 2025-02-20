/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:20:31 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/20 13:50:27 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void tokener(t_token **token, t_gc **g_collector, char *s_part) {
  int i;
  int start;
  char *word;
  char *spaces;
  char qoute;

  i = -1;
  spaces = " \n\t";
  if (!s_part)
    return ;
  while (s_part[++i]) {
    if (ft_strchr(spaces, s_part[i]))
      continue;
    else if ((ft_strchr("<|>", s_part[i]) && s_part[i + 1] == '\0') ||
             (s_part[0] == '|'))
      ft_error("bash: syntax error near unexpected token", &s_part[i], 2, g_collector);
    if (s_part[0] == '|')
      break;
    else if (s_part[i] == '<' && s_part[i + 1] == '<') {
      ft_lstadd_back(token, ft_lstnew(ft_strdup("<<", g_collector), T_REDIRECTE_HEREDOC, g_collector));
      i++;
    } else if (s_part[i] == '>' && s_part[i + 1] == '>') {
      ft_lstadd_back(token, ft_lstnew(ft_strdup(">>", g_collector), T_REDIRECTE_APPEND, g_collector));
      i++;
    } else if (s_part[i] == '<')
      ft_lstadd_back(token, ft_lstnew(ft_strdup("<", g_collector), T_REDIRECTE_IN, g_collector));
    else if (s_part[i] == '>')
      ft_lstadd_back(token, ft_lstnew(ft_strdup(">", g_collector), T_REDIRECTE_OUT, g_collector));
    else if (s_part[i] == '|')
      ft_lstadd_back(token, ft_lstnew(ft_strdup("|", g_collector), T_PIPE, g_collector));
    else if (s_part[i] == '\\' && ft_strchr("<|>", s_part[i + 1])) {
      ft_lstadd_back(token, ft_lstnew(ft_chrjoin('\\', s_part[i + 1], g_collector), T_WORD, g_collector));
      i++;
    } else {
      start = i;
      while (s_part[start] && !ft_strchr("<|>", s_part[start]) &&
             !ft_strchr(spaces, s_part[start])) {
        if (s_part[start] == '\'' || s_part[start] == '"') {
          qoute = s_part[start];
          start++;
          while (s_part[start] && s_part[start] != qoute)
            start++;
          if (s_part[start] == qoute)
            start++;
        }
        while (s_part[start] &&
               (s_part[start] != '\'' && s_part[start] != '"') &&
               !ft_strchr("<|>", s_part[start]) &&
               !ft_strchr(spaces, s_part[start]))
          start++;
      }
      // check for qoutations if are closed
      // word = (char *)malloc(sizeof(char *) * (start - i + 1));
      // printf("asdf%p \n", (*g_collector)->adress);
      word = gc(start - i + 1, g_collector);
      if (!word)
        ft_error("bash: cannot allocate memory for token",&s_part[start], 2, g_collector);
      ft_strlcpy(word, &s_part[i], start - i + 1);
      ft_lstadd_back(token, ft_lstnew(word, T_WORD, g_collector));
      i = start - 1;
    }
  }
}

void get_dir_files(char **dir_files, t_token *token, t_gc **g_collector) {
  if (!token || !token->next)
    return;
  if ((token->token_type == T_REDIRECTE_IN ||
       token->token_type == T_REDIRECTE_HEREDOC) &&
      token->token_type != T_PIPE) {
    *dir_files = ft_strjoin(*dir_files, token->value, g_collector);
    *dir_files = ft_strjoin(*dir_files, " ", g_collector);
    *dir_files = ft_strjoin(*dir_files, token->next->value, g_collector);
    *dir_files = ft_strjoin(*dir_files, " ", g_collector);
  } else if ((token->token_type == T_REDIRECTE_OUT ||
              token->token_type == T_REDIRECTE_APPEND) &&
             token->token_type != T_PIPE) {
    *dir_files = ft_strjoin(*dir_files, token->value, g_collector);
    *dir_files = ft_strjoin(*dir_files, " ", g_collector);
    *dir_files = ft_strjoin(*dir_files, token->next->value, g_collector);
    *dir_files = ft_strjoin(*dir_files, " ", g_collector);
  }
}

void get_command(char **only_command, t_token *token, t_gc **g_collector) {
  static int input_check;
  static int output_check;

  // apply a check for all the redirections and files skeep them and make sure
  // to get only the command no mutter if they are behinde the input or output
  // redirection sing
  if (token->token_type == T_REDIRECTE_OUT ||
      token->token_type == T_REDIRECTE_APPEND)
    output_check = 1;
  else if (token->token_type == T_REDIRECTE_IN ||
           token->token_type == T_REDIRECTE_HEREDOC)
    input_check = 1;
  else if (token->token_type == T_WORD &&
           (input_check == 1 || output_check == 1))
    (input_check = 0, output_check = 0);
  else if (token->token_type == T_WORD &&
           (input_check == 0 || output_check == 0)) {
    *only_command = ft_strjoin(*only_command, token->value, g_collector);
    *only_command = ft_strjoin(*only_command, " ", g_collector);
  }
}

t_token *init_data(t_token *token, char **dir_files, char **only_command, t_gc **g_collector)
{
  // free(*only_command);
  *only_command = NULL;
  // free(*dir_files);
  *dir_files = NULL;
  while (token && token->token_type != T_PIPE) {
    // get input and output directions as a string and files type
    get_dir_files(dir_files, token, g_collector);
    // get only command and there options as a single string
    get_command(only_command, token, g_collector);
    token = token->next;
  }
  // stop the loop at every pipe to consider all between pipes as single
  // separated node
  if (token && token->token_type == T_PIPE && token->next)
    return (token->next);
  return (NULL);
}

// void backslash_hander()
// {

// }

char *filer_qoutations(char *command_line,  t_gc **g_collector) {
  int i;
  int j;
  int in_qoute;
  char qoute;
  char *words_between;

  in_qoute = 0;
  j = 0;
  i = 0;
  if (!command_line)
    return (NULL);
  words_between = gc(ft_strlen(command_line) + 1, g_collector);
  if (!words_between)
    return (clear_bin(g_collector), NULL); // shoud handle
  while (command_line[i]) {
    if (command_line[i] == '\\' && command_line[i + 1] == '\0')
      printf("%s", "bash: unexpected EOF while looking for matching \\ \n");
    else if (command_line[i] == '\\' && in_qoute && qoute == '\'')
      ;
    else if (command_line[i] == '\\' && in_qoute && qoute == '"' &&
             command_line[i + 1] != qoute) {
      if (command_line[i + 1] == '\\' || command_line[i + 1] == '"')
        i++;
    } else if (command_line[i] == '\\') {
      i++;
      if (command_line[i] != '\0')
        words_between[j++] = command_line[i++];
      continue;
    }
    if ((command_line[i] == '"' || command_line[i] == '\'') && !in_qoute) {
      qoute = command_line[i];
      (in_qoute = 1, i++);
    } else if (command_line[i] == qoute && in_qoute)
      (in_qoute = 0, i++);
    else
      words_between[j++] = command_line[i++];
  }
  words_between[j] = '\0';
  if (in_qoute == 1)
    printf("bash : qoutations error `%c`\n", qoute); // shoud stop here
  return (words_between);
}

// void ft_free_2d(char **content) {
//   int i;

//   i = 0;
//   if (!content)
//     return;
//   while (content[i]) {
//     free(content[i]);
//     i++;
//   }
//   free(content);
// }

char **filterd(char **cmds, t_gc **g_collector)
{
  int i;

  i = 0;
  if (!cmds)
    return (NULL);
  while (cmds[i] != NULL)
  {
    cmds[i] = filer_qoutations(cmds[i], g_collector);
    i++;
  }
  return (cmds);
}

void parser(t_token **token,  t_gc **g_collector, t_data **data) {
  t_token *iter;
  char *dir_files;
  char *only_command;
  char **cmd_optios;

  dir_files = NULL;
  only_command = NULL;
  iter = *token;
  while (iter) {
    // loop until |
    iter = init_data(iter, &dir_files, &only_command, g_collector);
    // filter beside or secounded qoutes
    // only_command = filer_qoutations(only_command);
    cmd_optios = filterd(ft_split(only_command, ' ', g_collector), g_collector);
    // split redirections and command (with options) and pass them to creat a
    // new node (general structer) than add the node at the end of list
    add_data_back(data, new_data_node(cmd_optios, ft_split(dir_files, ' ', g_collector), g_collector));
  }
}

// void ft_free_tokens(t_token **token) {
//   t_token *hold;
//   t_token *iter;

//   iter = NULL;
//   iter = *token;
//   while (iter) {
//     hold = iter->next;
//     free(iter->value);
//     free(iter);
//     iter = hold;
//   }
//   *token = NULL;
// }

// void print_tokens(t_token **tokens) {
//   t_token *hold;

//   hold = *tokens;
//   while (hold) {
//     printf("(%s)\n", hold->value);
//     hold = hold->next;
//   }
// }

void parsing_case(t_token **tokens, t_data **data, t_gc **g_collector, char *line) {
  // split all the command line by four sings "< |>" and initial them in linked
  // list in shape of tokens
  tokener(tokens, g_collector, line);
  // print_tokens(tokens);
  // in parser fuction ill deal with all data amoung the pipes
  parser(tokens, g_collector, data);
}

int main(int ac, char **av, char **env) {
  (void)ac;
  (void)av;
  int status;
  char *line;
  t_token *tokens;
  t_data *data;
  t_gc *g_collector;

  status = 0;
  if (ac != 1)
    return (1);
  tokens = NULL;
  data = NULL;
  
  while (1) {
    g_collector = NULL;
    line = readline("\033[2;34mshell$> \033[0m");
    if (!line)
      exit(EXIT_SUCCESS);
    if (line[0] != '\0')
      add_history(line);
    // this function contains all paring cases
    parsing_case(&tokens, &data, &g_collector ,line);
    status = execute_package(&data, env, &g_collector);
    // print_tokens(&tokens);
    // while (g_collector && g_collector->next)
    // {
    //   printf("(%p)\n", g_collector->adress);
    //   g_collector = g_collector->next;
    // }
    printf("i am here\n");
    clear_bin(&g_collector);
  }
  return (0);
}
