#include "../../includes/minishell.h"
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

//TO_DO: handling expanding and ading the unlink to it so the file is not showd
char *get_file(t_gc **g_collector)
{
	char *num;
	char *file_name;
	int i;

	i = 0;
	while(1)
	{
		num = ft_itoa(i, g_collector);
		file_name = ft_strjoin ("/tmp/.her_doc" , ft_itoa(i, g_collector), g_collector);
		if (access(file_name, F_OK) == -1)
			return file_name;
		i++;
	}
}

int her_doc(char *limiter, t_gc **g_collector)
{
	int fd;
	char *line;
	char *file_name;
	int fd2;
	file_name = get_file(g_collector);
	fd = open_file(file_name, 1);
	fd2 = open_file(file_name, 0);
	unlink(file_name);
	while(1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf ("EOF detected");
			break;
		}
		else if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break;
		}
		else 
		{
			write(fd, line,  ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	close(fd);
	return fd2;
}
int	open_file(char *file, int in_or_out)
{

	int	ret;
	ret = 0;
	if (!file || file[0] == '\0') 
	{
		ft_error_exec_two("bash: ", file, ": No such file or directory", 2);
		return -1;
	}
	if (in_or_out == 0)
	{
		ret = open(file, O_RDONLY, 0644);
		if (ret == -1)
		{
			if (access(file, F_OK) == -1)
				ft_error_exec_two("bash: ", file, ": No such file or directory", 2);
			else if (access(file, R_OK) == -1)
				ft_error_exec_two("bash: ", file, ": Permission denied", 2);
		}
	}
	else if (in_or_out == 1)
	{
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ret == -1)
		{
			ft_error_exec_two("bash: ", file, ": Permission denied", 2);
			return -1;
		}	

	}
	else if (in_or_out == 2)
	{
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ret == -1)
		{
			ft_error_exec_two("bash: ", file, ": Permission denied", 2);
			return -1;
		}	
	}
	return (ret);
}

int	get_fds(t_data *list, t_gc **g_collector)
{
	char	**full_cmd;
	int		i;
	full_cmd = list->directions;
	i = 0;
	if (!full_cmd)
		return 0;
	while (full_cmd[i])
	{
		if (ft_strcmp(full_cmd[i], ">") == 0)
		{
			i++;
			if (list->out_fd != 0)
				close(list->out_fd);
			list->out_fd = open_file(full_cmd[i], 1);
			if (list->out_fd == -1)
				return 1;
		}
		else if (ft_strcmp(full_cmd[i], "<") == 0)
		{
			i++;
			if (list->in_fd != 0)
				close(list->in_fd);
			list->in_fd = open_file(full_cmd[i], 0);
			if (list->in_fd == -1)
				return 1;
		}
		else if (ft_strcmp(full_cmd[i], ">>") == 0)
		{
			i++;
			if (list->out_fd != 0)
				close(list->out_fd);
			list->out_fd = open_file(full_cmd[i], 2);
			if (list->out_fd == -1)
				return 1;
		}
		else if (ft_strcmp(full_cmd[i], "<>") == 0)
		{
			i++;
			close(open_file(full_cmd[i], 1));
		}
		else if (ft_strcmp(full_cmd[i], "<<") == 0)
		{
			i++;
			if (list->in_fd != 0)
				close(list->in_fd);
			list->in_fd = her_doc(full_cmd[i], g_collector);
				if (list->in_fd == -1)
					return 1;
		}
		i++;
		
	}	
	return 0;
}
