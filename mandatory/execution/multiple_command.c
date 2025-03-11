
#include "../../includes/minishell.h"

void	execute_first(t_data *current, int *p_fd, t_container *content)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("BASH: fork: Resource temporarily unavailable\n", 2);
		clean_fds(content->data);
		content->status = 1;
	}
	if (pid == 0)
	{
		if (get_fds(current, content) != 0)
			exit(1);
		close(p_fd[0]); // Close unused read end
		if (current->out_fd == 0)
			current->out_fd = p_fd[1];
		else
			close(p_fd[1]); // Close write end if already set
		if (check_builtin_commands(current->cmds))
		{	
			(built_in(current ,content));
			exit(content->status);
		}
		if (current->in_fd != 0)
		{
			if (dup2(current->in_fd, 0) < 0)
			{
				perror("dup2 in_fd");
				exit(1);
			}
		}
		if (dup2(current->out_fd, 1) < 0)
		{
			perror("dup2 out_fd");
			exit(1);
		}
		if (current->in_fd != 0)
			close(current->in_fd);
		if (current->out_fd != 0)
			close(current->out_fd);
		
		executing(current , content);
	}
	close(p_fd[1]);
}
static void	execut(t_container *content, t_data *current, int *p_fd, int in)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("BASH: fork: Resource temporarily unavailable\n", 2);
		clean_fds(content->data);
		content->status = 1;
	}
	if (pid == 0)
	{
		if (get_fds(current,  content) != 0)
			exit(1);
		close(p_fd[0]); // Close unused read end
		if (current->out_fd == 0)
			current->out_fd = p_fd[1];
		else
			close(p_fd[1]); // Close write end if already set
		if (current->in_fd == 0)
			current->in_fd = in;
		else
			close(in); // Close previous pipe input
		if (check_builtin_commands(current->cmds))
		{	
			(built_in(current ,content));
			exit(content->status);
		}
		if (dup2(current->in_fd, 0) < 0)
		{
			perror("dup2 in_fd");
			exit(1);
		}
		if (dup2(current->out_fd, 1) < 0)
		{
			perror("dup2 out_fd");
			exit(1);
		}
		executing(current , content);
	}
	close(p_fd[1]); // Close write end in parent
	close(in);      // Close previous pipe input in parent
}

int	execute_last(t_container *content, t_data *current, int *p_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("BASH: fork: Resource temporarily unavailable\n", 2);
		clean_fds(content->data);
	}
	if (pid == 0)
	{
		if (get_fds(current, content) != 0)
			exit(1);
		if (current->in_fd == 0)
			current->in_fd = p_fd[0];
		else
			close(p_fd[0]); // Close read end if already set
		if (check_builtin_commands(current->cmds))
		{	
			(built_in(current ,content));
			exit(content->status);
		}
		if (current->in_fd != 0)
		{
			if (dup2(current->in_fd, 0) < 0)
			{
				perror("dup2 in_fd");
				exit(1);
			}
		}
		if (current->out_fd != 0)
		{
			if (dup2(current->out_fd, 1) < 0)
			{
				perror("dup2 out_fd");
				exit(1);
			}
		}
		executing(current , content);
	}
	close(p_fd[0]); // Close read end in parent
	return (pid);
}

static int	handle_pipes(t_container *content)
{
	int		p_fd[2];
	t_data	*current;

	current = content->data;
	if (pipe(p_fd) == -1)
		exit(1);
	execute_first(current, p_fd, content);
	current = current->next;
	while (current != NULL && current->next != NULL)
	{
		int t = p_fd[0]; // Save previous pipe read end
		if (pipe(p_fd) == -1)
			exit(1);
		execut(content, current, p_fd, t);
		close(t);
		current = current->next;
		close(p_fd[1]);
	}
	return (execute_last(content, current, p_fd));
}

void	run_multiple(t_container *content)
{
	int	status;
	int	exit_code;
	int	id_last_command;

	status = 0;
	exit_code = 0;
	id_last_command = handle_pipes(content);
	waitpid(id_last_command, &content->status, 0);
	update_status(content);
	while (wait(NULL) > 0)
		;
	
}
