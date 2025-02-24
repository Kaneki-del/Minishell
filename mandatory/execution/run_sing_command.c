#include "../../includes/minishell.h"

int	single_command(t_container *content)
{
	pid_t	pid;
	int		status;
	t_data *current = content->data;
	if (!current->cmds || !current->cmds[0])
		return 0;
	status = 0;
	if (check_builtin_commands(current->cmds))
		return (built_in(content));
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{ // Child process
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
