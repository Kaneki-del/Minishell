/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:21 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/21 01:30:19 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	max_herdoc(char **rideractions)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!rideractions || !rideractions[0])
		return (0);
	while (rideractions[i])
	{
		if (ft_strcmp(rideractions[i], "<<") == 0)
			count++;
		i++;
	}
	if (count > 16)
		return (1);
	return (0);
}

static void	intial(t_data **list)
{
	t_data	*current;

	if (!list)
		return ;
	current = NULL;
	current = *list;
	while (current)
	{
		current->in_fd = 0;
		current->out_fd = 0;
		current = current->next;
	}
}

int	get_herdocs(t_data **list, t_container *content)
{
	t_data	*current;

	current = NULL;
	current = *list;
	while (current)
	{
		if (max_herdoc(current->directions) == 1)
		{
			ft_error_exec_two("mshell: ", "maximum here-document",
				" count exceeded", 2);
			clean_fds(*list);
			clear_bin(&content->g_collector);
			clear_bin(&content->g_env_collector);
			exit(2);
		}
		else if (prioritize_herdoc(current, current->directions, content) == -3)
			return (-3);
		current = current->next;
	}
	return (0);
}

void	execute_package(t_container *content)
{
	int	list_size;

	content->status = 0;
	content->fork_failed = 0;
	if (!content->data)
		return ;
	list_size = ft_lstsize(content->data);
	intial(&content->data);
	if (get_herdocs(&content->data, content) == -3)
		return ;
	signal(SIGINT, ctrl_cmd);
	signal(SIGQUIT, ctrl_cmd);
	if (list_size == 1)
	{
		if (get_fds(content->data, content) != 0)
			content->status = 1;
		else
			single_command(content);
	}
	else if (list_size >= 2)
		run_multiple(content);
	clean_fds(content->data);
	tcsetattr(STDERR_FILENO, TCSANOW, &content->termios_value);
}
