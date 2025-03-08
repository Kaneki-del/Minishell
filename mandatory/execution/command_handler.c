#include "../../includes/minishell.h"

static void	intial(t_data **list)
{
	t_data	*current;

	current = NULL;
	current = *list;
	while (current)
	{
		current->in_fd = 0;
		current->out_fd = 0;
		current = current->next;
	}
}
static void	ctrl_cmd(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit\n", 5);
}
int	execute_package(t_container *content)
{
	signal(SIGINT, ctrl_cmd);
	signal(SIGQUIT, ctrl_cmd);
	int	list_size;
	int	exit_code;
	exit_code = 0;
	if (!content->data)
		return 0; 
	list_size = ft_lstsize(content->data);
	intial(&content->data);
	if (list_size == 1)
	{
		if ( get_fds(content->data, &content->g_collector) != 0)
			return 1;
		
		exit_code = single_command(content);
	}
	else if (list_size >= 2)
		exit_code = run_multiple(content);
	tcsetattr(STDERR_FILENO, TCSANOW, &content->termios_value);
	// tcsetattr(STDERR_FILENO, TCSANOW, &content->termios_value); 
	return (exit_code);
}
