#include "../../includes/minishell.h"

int	single_command(t_container *content)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (check_builtin_commands(content->data->cmds))
		return (built_in(content));
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{ // Child process
		if (content->data->in_fd != 0)
		{
			if (dup2(content->data->in_fd, 0) < 0)
			{
				close(content->data->in_fd);
				close(content->data->out_fd);
				exit(1);
			}
			close(content->data->in_fd);
		}
		if (content->data->out_fd != 0)
		{
			if (dup2(content->data->out_fd, 1) < 0)
			{
				close(content->data->out_fd);
				exit(1);
			}
			close(content->data->out_fd);
		}
		executing(content);
	}
	else
	{ // Parent process
		if (content->data->in_fd != 0)
			close(content->data->in_fd);
		if (content->data->out_fd != 0)
			close(content->data->out_fd);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
	}
	return (1);
}
