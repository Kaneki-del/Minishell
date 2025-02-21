/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:20:31 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/21 22:55:10 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void ft_print2d(char **str)
// {
//   int i;

//   i = 0;
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
//     ft_print2d(iter->cmds);
//     printf("\n");
//     ft_print2d(iter->directions);
//     printf("\n");
//     iter = iter->next;
//   }
// }


// void ft_printf(t_token **data)
// {
//   t_token *iter;

//   iter = *data;
//   while (iter)
//   {
//     printf("[%s]\n", iter->value);
//     iter = iter->next;
//   }
// }

int main(int ac, char **av, char **env) {
  (void)ac;
  (void)av;
  int status;
  char *line;
  t_token *tokens;
  t_data *data;
  t_gc *g_collector;
  // our local env
  t_env *env_list;
  env_list = get_env_list(env);
  while (1) {
    //remember to remove it from here
    status = 0;
    tokens = NULL;
    data = NULL;
    g_collector = NULL;
    line = readline("\033[2;34mshell$> \033[0m");
    if (!line)
      exit(EXIT_SUCCESS);
    if (line[0] != '\0')
      add_history(line);
    // this function contains all paring cases
    if (parsing_case(&tokens, &data, &g_collector ,line, &env_list) == 0)
      continue;
    // ft_printf(&tokens);
    status = execute_package(&data, &g_collector, &env_list);
    free(line);
    clear_bin(&g_collector);
  }
  return (0);
}
