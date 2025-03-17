/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/17 15:03:19 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ctrl_c(int sig) {
  printf("\n");
  // if (g_sig == 4)
  //   close(0);

  g_sig = sig;
  rl_on_new_line();
  rl_replace_line("", 0);
  rl_redisplay();
}
void ft_print2d(char **str) {
  int i;

  i = 0;
  if (!str)
    return;
  while (str[i]) {
    printf("%s ", str[i]);
    i++;
  }
}

// void f()
// {
//   system("lsof -c minishell");
// }
void ft_printf(t_data **data) {
  t_data *iter;

  iter = *data;
  while (iter) {
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

void init_content(t_container *content) {
  content->tokens = NULL;
  content->data = NULL;
  content->save_path = NULL;
  content->line = NULL;
  content->is_expandable = 0;
  content->flag = 0;
  content->new_command = NULL;
}

int main(int ac, char **av, char **env) {
  (void)av;
  (void)ac;

  t_container content;
  tcgetattr(STDERR_FILENO, &content.termios_value);
  content.g_env_collector = NULL;
  content.g_collector = NULL;
  content.env_list = get_env_list(env, &content);
  content.status = 0;
  rl_catch_signals = 0;
  while (1) {

    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ctrl_c);
    /*   if (ac != 1 || !isatty(0)) */
    /* return (1); */
    init_content(&content);
    content.line = readline("mshell$> ");
    if (g_sig == 2) {
      content.status = 1;
      g_sig = 0;
    }
    if (!content.line) {
      printf("exit\n");
      free(content.line);
      clear_bin(&content.g_env_collector);
      clear_bin(&content.g_collector);
      exit(content.status);
    }
    if (content.line[0] != '\0')
      add_history(content.line);
    if (parsing_case(&content) == 0) {
      free(content.line);
      clear_bin(&content.g_collector);
      content.g_collector = NULL;
      continue;
    }
    execute_package(&content);
    free(content.line);
    clear_bin(&content.g_collector);
    content.g_collector = NULL;
    content.line = NULL;
  }
}
