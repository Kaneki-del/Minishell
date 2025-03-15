#include "../../includes/minishell.h"


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
int prioritize_herdoc(t_data *list, char **rideractions, t_container *content)
{
	int i;
	
	if (!rideractions || !rideractions[0])
		return 0;
	i = 0;
	while (rideractions[i])
	{
		if (ft_strcmp(rideractions[i], "<<") == 0)
		{
			i++;
			if (list->in_fd != 0)
				close(list->in_fd);
			list->in_fd = her_doc(rideractions[i], content);
			if (list->in_fd == -3)
					return -3;
		}
		i++;
	}
	return 0;
}
int rediractions_out(t_data *list, int fd, int i)
{
	i++;
	if (list->out_fd != 0)
		close(list->out_fd);
	list->out_fd = open_file(list->directions[i], fd);
	if (list->out_fd == -1)
		return 1;
	return 0;
}
int rideractions_handler(t_data *list, int i)
{
	if (ft_strcmp(list->directions[i], ">") == 0)
	{
		if (rediractions_out(list, 1, i) == 1)
			return 1;
	}
	else if (ft_strcmp(list->directions[i], "<") == 0)
	{
			i++;
			if (list->in_fd != 0)
				close(list->in_fd);
			list->in_fd = open_file(list->directions[i], 0);
			if (list->in_fd == -1)
				return 1;
	}
	else if (ft_strcmp(list->directions[i], ">>") == 0)
	{
		if (rediractions_out(list, 2, i) == 1)
			return 1;
	}
	return 0;	
}

int	get_fds(t_data *list, t_container *content)
{
	(void)content;

	char	**full_cmd;
	int		i;

	full_cmd = list->directions;
	i = 0;
	if (!full_cmd || !full_cmd[0])
		return 0;
	while (full_cmd[i])
	{
		if (rideractions_handler(list, i) == 1)
			return 1;
		i++;
	}
	return 0;
}
