#include "../../includes/minishell.h"

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

int parser(t_token **token,  t_gc **g_collector, t_data **data, t_env **env_list)
{
  t_token *iter;
  char *dir_files;
  char *only_command;
  char **cmd_optios;

  dir_files = NULL;
  only_command = NULL;
  iter = *token;
  (void)env_list;
  while (iter)
  {
    // loop until |
    iter = init_data(iter, &dir_files, &only_command, g_collector);
    // filter beside or secounded qoutes
    // only_command = filer_qoutations(only_command);
    only_command = check_env_var(only_command, env_list, g_collector);
    cmd_optios = filterd(ft_split(only_command, ' ', g_collector), env_list, g_collector);
    if (!cmd_optios)
      return (0);
    // split redirections and command (with options) and pass them to creat a
    // new node (general structer) than add the node at the end of list
    add_data_back(data, new_data_node(cmd_optios, ft_split(dir_files, ' ', g_collector), g_collector));
  }
  return (1);
}

int token_checker(t_token **tokens, t_gc **g_collector)
{
  t_token *iter;

  if (!tokens)
    return (0);
  iter = *tokens;
  while (iter && iter->next)
  {
    if (iter->token_type == T_PIPE && iter->next->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);

    if (iter->token_type == T_REDIRECTE_IN && iter->next->token_type == T_REDIRECTE_IN)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_IN && iter->next->token_type == T_REDIRECTE_OUT)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_IN && iter->next->token_type == T_REDIRECTE_HEREDOC)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_IN && iter->next->token_type == T_REDIRECTE_APPEND)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_IN && iter->next->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);

    if (iter->token_type == T_REDIRECTE_OUT && iter->next->token_type == T_REDIRECTE_OUT)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_OUT && iter->next->token_type == T_REDIRECTE_IN)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_OUT && iter->next->token_type == T_REDIRECTE_HEREDOC)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_OUT && iter->next->token_type == T_REDIRECTE_APPEND)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_OUT && iter->next->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);

    if (iter->token_type == T_REDIRECTE_APPEND && iter->next->token_type == T_REDIRECTE_APPEND)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_APPEND && iter->next->token_type == T_REDIRECTE_HEREDOC)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_APPEND && iter->next->token_type == T_REDIRECTE_OUT)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_APPEND && iter->next->token_type == T_REDIRECTE_IN)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_APPEND && iter->next->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);

    if (iter->token_type == T_REDIRECTE_HEREDOC && iter->next->token_type == T_REDIRECTE_HEREDOC)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_HEREDOC && iter->next->token_type == T_REDIRECTE_APPEND)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_HEREDOC && iter->next->token_type == T_REDIRECTE_IN)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_HEREDOC && iter->next->token_type == T_REDIRECTE_OUT)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    if (iter->token_type == T_REDIRECTE_HEREDOC && iter->next->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, g_collector), 0);
    iter = iter->next;
  }
  return (1);
}

int parsing_case(t_token **tokens, t_data **data, t_gc **g_collector, char *line, t_env **env_list)
{
  // split all the command line by four sings "< |>" and initial them in linked
  // list in shape of tokens
  if (tokener(tokens, g_collector, line) == 0)
    return (0);
  if (token_checker(tokens, g_collector) == 0)
    return (0);
  // in parser fuction ill deal with all data amoung the pipes
  if (parser(tokens, g_collector, data, env_list) == 0)
    return (0);
  return (1);
}
