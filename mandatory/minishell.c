/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/23 20:31:03 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

// void ft_print2d(char **str)
// {
//   int i;

//   i = 0;
//   if (!str)
//     return ;
//   while (str[i])
//   {
//     printf("%s ", str[i]);
//     i++;  
//   }
// }
// void ft_printf(t_data **data)
// {
//   t_data *iter;

//   iter = *data;
//   while (iter)
//   {
//     printf("\n");
//     printf("================================\n");
//     printf("\n");
//     printf("\n");
//     printf("COMMAND   : ");
//     ft_print2d(iter->cmds);
//     printf("\n");
//     printf("DIRECTION : ");
//     ft_print2d(iter->directions);
//     printf("\n");
//     printf("\n");
//     printf("================================\n");
//     printf("\n");
//     iter = iter->next;
//   }
// }

int main(int ac, char **av, char **env) {
  (void)ac;
  (void)av;

  t_container content;
  content.g_env_collector = NULL;
  content.env_list = get_env_list(env, &content);
  content.status = 0;
  while (1) {
    
    //remember to remove it from here
    content.tokens = NULL;
    content.data = NULL;
    content.g_collector = NULL;
    content.line = readline("\033[2;34mshell$> \033[0m");
    if (!content.line)
      exit(EXIT_SUCCESS);
    if (content.line[0] != '\0')
      add_history(content.line);
    // this function contains all paring cases
    if (parsing_case(&content) == 0)
      continue;
    // ft_printf(&content.data);
    if (execute_package(&content) == 0)
      continue;
    free(content.line);
    clear_bin(&content.g_collector);
  }
  return (0);
}
