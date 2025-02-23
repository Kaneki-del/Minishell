#include "../../includes/minishell.h"

static void	intial(t_data **list)
{
	t_data	*current;

	current = *list;
	while (current)
	{
		current->in_fd = 0;
		current->out_fd = 0;
		current = current->next;
	}
}

int	execute_package(t_container *content)
{
	int	list_size;
	int	exit_code;

	exit_code = 0;
	if (!content->data)
	{
		clear_bin(&content->g_collector);
		return 0; // check here
	}
	list_size = ft_lstsize(content->data);
	intial(&content->data);
	if (list_size == 1)
	{
		get_fds(content->data);
		exit_code = single_command(content);
	}
	else if (list_size >= 2)
	{
		exit_code = run_multiple(content);
	}
	return (exit_code);
}
