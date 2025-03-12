#include "../../includes/minishell.h"


char *get_file(t_gc **g_collector)
{
	char *file_name;
	int i;

	i = 0;
	while(1)
	{
		file_name = ft_strjoin ("/tmp/.her_doc" , ft_itoa(i, g_collector), g_collector);
		if (access(file_name, F_OK) == -1)
			return file_name;
		i++;
	}
}
void	ctrl_c_heredoc(int sig)
{
	close(0);
	g_sig = sig;
}
int	hrdc_ctrlc(int fd, t_container *content)
{
	if (g_sig)
	{
		content->status = 1;
		if (dup2(fd, 0) == -1)
		{
			close(fd);
			return (1);
		}
		close(fd);
		return (1);

	}
	return (0);
}
int her_doc(char *limiter, t_container *content)
{
	int fd1;
	char *line;
	char *file_name;
	int fd2;
	int flag;

	signal(SIGINT, ctrl_c_heredoc);
	int fd = dup(0);
	if (fd == -1)
		return (ft_putstr_fd("error\n", 0), 1);
	flag = 0;
	file_name = get_file(&content->g_collector);
	fd1 = open_file(file_name, 1);
	fd2 = open_file(file_name, 0);
	unlink(file_name);
	while(!g_sig)
	{
			line = readline("> ");
			if (line == NULL)
				break; 
			else if (ft_strcmp(line, filer_qoutations(limiter, &content->g_collector)) == 0)
			{
				free(line);
				line = NULL;
				break; 
			}
			else 
			{
				if (check_is_in_qoutes(limiter) == 0)
					line = filer_qoutations(check_env_var(content, line, &flag, 1), &content->g_collector);
				if (line)
				{
					write(fd, line,  ft_strlen(line));
					write(fd, "\n", 1); 
					line = NULL; // free line lead to a segfult
				}
				else
					write(fd, "\n", 1); 
			}
	}
	if (hrdc_ctrlc(fd, content) == 0)
	{
		close(fd1);
		close(fd2);
		return (0);
	}
	close(fd1);
	return fd2;
}