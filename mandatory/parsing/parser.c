#include "../../includes/minishell.h"

t_token *init_data(t_token *token, char **dir_files, char **only_command, t_gc **g_collector)
{
  // free(*only_command);
  *only_command = NULL;
  // free(*dir_files);
  *dir_files = NULL;
  while (token && token->token_type != T_PIPE)
  {
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

int token_checker(t_container *content)
{
  t_token *iter;

  if (!content->tokens)
    return (0);
  iter = content->tokens;
  if (iter->token_type == T_PIPE)
        return (ft_error("bash: syntax error near unexpected token", "|", 2, &content->g_collector), 0);
  while (iter && iter->next)
  {
    if (iter->token_type == T_PIPE && iter->next->token_type == T_PIPE)
      return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2, &content->g_collector), 0);
    if (redirection_pipe_check (iter, T_REDIRECTE_IN, &content->g_collector) == 0)
      return (0);
    if (redirection_pipe_check (iter, T_REDIRECTE_OUT, &content->g_collector) == 0)
      return (0);
    if (redirection_pipe_check (iter, T_REDIRECTE_APPEND, &content->g_collector) == 0)
      return (0);
    if (redirection_pipe_check (iter, T_REDIRECTE_HEREDOC, &content->g_collector) == 0)
      return (0);
    iter = iter->next;
  }
  if (iter->next == NULL && (iter->token_type == T_PIPE || iter->token_type == T_REDIRECTE_IN || \
  iter->token_type == T_REDIRECTE_OUT || iter->token_type == T_REDIRECTE_APPEND || iter->token_type == T_REDIRECTE_HEREDOC))
      return (ft_error("bash: syntax error near unexpected token", "newline", 2, &content->g_collector), 0);
  return (1);
}

size_t	ft_strlen_2d(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int parser(t_container *content)
{
  t_token *iter;
  char *dir_files;
  char *only_command;
  char **cmd_optios;
  int flag;

  dir_files = NULL;
  only_command = NULL;
  cmd_optios = NULL;
  iter = content->tokens;
  flag = 1;
  while (iter)
  {
    // loop until |
    iter = init_data(iter, &dir_files, &only_command, &content->g_collector);
    // filter beside or secounded qoutes
    // only_command = filer_qoutations(only_command);
    if (only_command)
    {
      flag = 2;
      only_command = check_env_var(content, only_command, &flag, 0);
    }
    if (dir_files)
    {
      flag = 1;
      dir_files = check_env_var(content, dir_files, &flag, 0);
    }
    if (flag == 0)
    {
      clear_bin(&content->g_collector);
      return (0);
    }
    // if (only_command && ft_strncmp(only_command, "export ", 7) == 0 )
    // {
    //     cmd_optios = ft_split(only_command, ' ', &content->g_collector);
    // }
    // else
    // {
    //   // this is not working at qoutations cases
    //   if (flag == 5)
    //     only_command = filter_one_sides(only_command, &content->g_collector);
    //   cmd_optios = filterd(ft_split(only_command, ' ', &content->g_collector), &content->g_collector);
    // }
    // printf("(%d)\n", flag);
    // printf("(%s)\n", only_command);
    if (only_command && ft_strncmp(only_command, "export ", 7) == 0 && flag == 5)
    {
        // only_command = add_qoutations(only_command);

        cmd_optios = ft_split(only_command, ' ', &content->g_collector);
        if(ft_strlen_2d(cmd_optios) < 3)
        {
          cmd_optios[1] = filer_qoutations(ft_strdup(only_command + 7, &content->g_collector),  &content->g_collector);
          cmd_optios[2] = NULL;
        }
        else
        {
          cmd_optios = filterd(cmd_optios, &content->g_collector);
        }
    }
    else
    {
      only_command = filter_one_sides(only_command, &content->g_collector);
      cmd_optios = filterd(ft_split(only_command, ' ', &content->g_collector), &content->g_collector);
    }
    cmd_optios = check_echo_options(cmd_optios, &content->g_collector);
    // dir_files = filer_qoutations(dir_files, &content->g_collector);
    // split redirections and command (with options) and pass them to creat a
    // new node (general structer) than add the node at the end of list
    add_data_back(&content->data, new_data_node(cmd_optios, filterd(ft_split(dir_files, ' ', &content->g_collector), &content->g_collector), &content->g_collector));
  }
  return (1);
}

int parsing_case(t_container *content)
{
  // split all the command line by four sings "< |>" and initial them in linked
  // list in shape of tokens
  if (tokener(content) == 0)
    return (0);
  if (token_checker(content) == 0)
    return (0);
  // in parser fuction ill deal with all data amoung the pipes
  if (parser(content) == 0)
    return (0);
  return (1);
}
