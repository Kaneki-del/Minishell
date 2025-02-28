#include "../../includes/minishell.h"

void get_dir_files(char **dir_files, t_token *token, t_gc **g_collector)
{
  if (!token || !token->next)
    return;
  if ((token->token_type == T_REDIRECTE_IN ||
       token->token_type == T_REDIRECTE_HEREDOC) &&
      token->token_type != T_PIPE) {
    *dir_files = ft_strjoin(*dir_files, token->value, g_collector);
    if (token->next != NULL)
      *dir_files = ft_strjoin(*dir_files, " ", g_collector);
    *dir_files = ft_strjoin(*dir_files, token->next->value, g_collector);
    if (token->next->next != NULL)
      *dir_files = ft_strjoin(*dir_files, " ", g_collector);
  } else if ((token->token_type == T_REDIRECTE_OUT ||
              token->token_type == T_REDIRECTE_APPEND) &&
             token->token_type != T_PIPE) {
    *dir_files = ft_strjoin(*dir_files, token->value, g_collector);
    if (token->next != NULL)
      *dir_files = ft_strjoin(*dir_files, " ", g_collector);
    *dir_files = ft_strjoin(*dir_files, token->next->value, g_collector);
    if (token->next->next != NULL)
      *dir_files = ft_strjoin(*dir_files, " ", g_collector);
  }
}

void get_command(char **only_command, t_token *token, t_gc **g_collector)
{
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
  else if (token->token_type == T_WORD && (input_check == 1 || output_check == 1))
    (input_check = 0, output_check = 0);
  else if (token->token_type == T_WORD &&
           (input_check == 0 || output_check == 0)) {
    *only_command = ft_strjoin(*only_command, token->value, g_collector);
    if (token && token->next && token->next->token_type != T_PIPE)
      *only_command = ft_strjoin(*only_command, " ", g_collector);
  }
}
