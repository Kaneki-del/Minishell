/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/28 12:15:46 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

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

void f()
{
  system("lsof -c minishell");
}
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
    
}
int main(int ac, char **av, char **env) {
  (void)ac;
  (void)av;

  atexit(f);
  t_container content;
  content.g_env_collector = NULL;
  content.g_collector = NULL;
  content.env_list = get_env_list(env, &content);
  content.status = 0;
  while (1) {
    
    //remember to remove it from here
	init_content(&content);
    content.line = readline("\033[2;34mshell$> \033[0m");
    if (!content.line)
      exit(EXIT_SUCCESS);
    if (content.line[0] != '\0')
      add_history(content.line);
    // this function contains all paring cases
    if (parsing_case(&content) == 0)
      continue;
    ft_printf(&content.data);
    content.status = execute_package(&content); 
    free(content.line);
    clear_bin(&content.g_collector);
    content.g_collector = NULL;
  }
   clear_bin(&content.g_env_collector);
  return (0);
}
