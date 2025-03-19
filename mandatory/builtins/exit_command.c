/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:53:58 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/19 01:00:40 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	filter_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
		return 1;
	while (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (arg[i] == '\0')
		return 1;
	if ((arg[i] == '+' || arg[i] == '-') && arg[i + 1] != '\0')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	chek_args_number(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
void exit_p(t_container *content)
{
	if (content->if_pipe != PIPE)
		ft_putstr_fd("exit\n", 2);
}
static int	filter_exit(t_container *content, char **args)
{
	if (filter_args(args[0]) == 1)
	{
		exit_p(content);
		ft_error_exec_two("mshell: exit: ", args[0],
			": numeric argument required", 2);
		clean_fds(content->data);
		clear_bin(&content->g_collector);
		clear_bin(&content->g_env_collector);
		exit(255);
	}
	if (chek_args_number(args + 1) > 0)
	{
		exit_p(content);
		ft_putstr_fd("mshell: exit: too many arguments\n", 2);
		content->status = 1;
		return (1);
	}
	return (0);
}

static void	clean_exit(t_container *content, int exit_code)
{
	clean_fds(content->data);
	clear_bin(&content->g_collector);
	clear_bin(&content->g_env_collector);
	if (content->if_pipe != PIPE)
		write(1, "exit\n", 5);
	exit(exit_code);
}

void	handle_exit(t_data *current, t_container *content)
{
	char	**args;
	ssize_t	number;
	int		exit_code;

	args = current->cmds + 1;
	exit_code = 0;
	if (args[0])
	{
		if (filter_exit(content, args))
			return ;
		number = ft_atoi(args[0], current, content);
		exit_code = number % 256;
		if (exit_code < 0)
			exit_code += 256;
		clean_exit(content, exit_code);
	}
	else
		clean_exit(content, 0);
}
