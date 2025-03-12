#include "../../includes/minishell.h"

int max_herdoc(char **rideractions)
{
	int count;
	int i;

	i = 0;
	count = 0;
	if (!rideractions || !rideractions[0])
		return 0;
	while (rideractions[i])
	{
		if (ft_strcmp(rideractions[i], "<<") == 0)
			count++;
		i++;
	}
	if (count > 16)
		return 1;
	return 0;
}

static void	intial(t_data **list, t_container *content)
{
	t_data	*current;
	
	current = NULL;
	current = *list;
	while (current)
	{
		if (max_herdoc(current->directions) == 1)
		{
			ft_error_exec_two("bash: ", "maximum here-document", " count exceeded", 2);
			clean_fds(*list);
			clear_bin(&content->g_collector);
			clear_bin(&content->g_env_collector);
			exit(2);
		}
		current->in_fd = 0;
		current->out_fd = 0;
		current = current->next;
	}
}
 void	ctrl_cmd(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit\n", 5);
	else if (sig == SIGINT)
		write(1, "\n", 3);
}
void	execute_package(t_container *content)
{
	signal(SIGINT, ctrl_cmd);
	signal(SIGQUIT, ctrl_cmd);
	int	list_size;
	content->status = 0;
	if (!content->data)
		return;
	list_size = ft_lstsize(content->data);
	intial(&content->data, content);
	if (list_size == 1)
	{
		if ( get_fds(content->data, content) != 0)
			content->status = 1; 
		else 
			single_command(content);
	}
	else if (list_size >= 2)
		run_multiple(content);
	tcsetattr(STDERR_FILENO, TCSANOW, &content->termios_value);
}
