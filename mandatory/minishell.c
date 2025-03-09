/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/09 16:22:53 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
void	ctrl_c(int sig)
{
	printf("\n");
	sig_var = sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void ft_print2d(char **str)
{
  int i;

  i = 0;
  if (!str)
    return ;
  while (str[i])
  {
    printf("%s ", str[i]);
    i++;  
  }
}

// void f()
// {
//   system("lsof -c minishell");
// }
void ft_printf(t_data **data)
{
  t_data *iter;

  iter = *data;
  while (iter)
  {
    printf("\n");
    printf("================================\n");
    printf("\n");
    printf("\n");
    printf("COMMAND   : ");
    ft_print2d(iter->cmds);
    printf("\n");
    printf("DIRECTION : ");
    ft_print2d(iter->directions);
    printf("\n");
    printf("\n");
    printf("================================\n");
    printf("\n");
    iter = iter->next;
  }
}

void init_content(t_container *content)
{
	  content->tokens = NULL;
    content->data = NULL;
    content->line = NULL;
    content->is_expandable = 0;
}

int main(int ac, char **av, char **env)
{
  (void)ac;
  (void)av;

  // atexit(f);
  t_container content;
  content.g_env_collector = NULL;
  content.g_collector = NULL;
  content.env_list = get_env_list(env, &content);
  content.status = 0;
  while (1) {

    //remember to remove it from here
    if (ac != 1 || !isatty(0))
		return (1);
    rl_catch_signals = 0;
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ctrl_c);
    init_content(&content);
  
    content.line = readline("mshell$> ");
    if (!content.line)
      exit(EXIT_SUCCESS);
    if (content.line[0] != '\0')
      add_history(content.line);
    // this function contains all paring cases
    if (parsing_case(&content) == 0) // shoud move the clear_bin here
    {
      free(content.line);
      content.g_collector = NULL;
      continue;
    }
    // ft_printf(&content.data);
    content.status = execute_package(&content); 
    free(content.line);
    clear_bin(&content.g_collector);
    content.g_collector = NULL;
    content.line = NULL;
  }
   clear_bin(&content.g_env_collector);
  return (0);
}
