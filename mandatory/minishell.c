/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:20:16 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/23 00:30:19 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_content(t_container *content)
{
	content->tokens = NULL;
	content->data = NULL;
	content->save_path = NULL;
	content->line = NULL;
	content->flag = 1;
	content->is_status = 0;
	content->new_command = NULL;
	content->if_pipe = 0;
}

static int	repeat_line(t_container *content)
{
	if (g_sig == 2)
	{
		content->status = 1;
		g_sig = 0;
	}
	if (!content->line)
	{
		write(1, "exit\n", 6);
		clean_exit2(content, content->status);
	}
	if (content->line[0] != '\0')
		add_history(content->line);
	if (parsing_case(content) == 0)
	{
		free(content->line);
		clear_bin(&content->g_collector);
		content->g_collector = NULL;
		return (1);
	}
	execute_package(content);
	free(content->line);
	clear_bin(&content->g_collector);
	content->g_collector = NULL;
	content->line = NULL;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_container	content;

	(void)av;
	tcgetattr(STDERR_FILENO, &content.termios_value);
	content.g_env_collector = NULL;
	content.g_collector = NULL;
	content.env_list = get_env_list(env, &content);
	content.status = 0;
	rl_catch_signals = 0;
	while (1)
	{
		if (ac != 1 || !isatty(0))
			return (1);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c);
		init_content(&content);
		content.line = readline("mshell$> ");
		if (repeat_line(&content))
			continue ;
	}
}
