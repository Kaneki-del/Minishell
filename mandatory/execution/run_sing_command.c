#include "../../includes/minishell.h"
// static void	ctrl_cmd(int sig)
// {
// 	if (sig == SIGQUIT)
// 		write(1, "Quit\n", 5);
// }

int	single_command(t_container *content)
{
	pid_t	pid;
	int		status;
	t_data *current = content->data;
	if (!current->cmds || !current->cmds[0])
	{
		content->status = 0;
		return;
	}
	status = 0;
	if (check_builtin_commands(current->cmds))
		return (built_in(current, content));
	
	pid = fork();
	if (pid < 0)
	{
		clean_fds(current);
	}
	if (pid == 0)
	{
		if (current->in_fd != 0)
		{
			if (dup2(current->in_fd, 0) < 0)
			{
				close(current->in_fd);
				close(current->out_fd);
				exit(1);
			}
			close(current->in_fd);
		}
		if (current->out_fd != 0)
		{
			if (dup2(current->out_fd, 1) < 0)
			{
				close(current->out_fd);
				exit(1);
			}
			close(current->out_fd);
		}
		executing(current,content);
	}
	else
		if (content->data->in_fd != 0)
			close(content->data->in_fd);
		if (content->data->out_fd != 0)
			close(content->data->out_fd);
		waitpid(pid, &content->status, 0);
		update_status(content);
	
}
