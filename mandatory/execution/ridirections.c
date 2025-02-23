#include "../../includes/minishell.h"

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0644);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ret == -1)
	{
		ft_putstr_fd("bash: no such file or directory: ", 2);
		ft_putstr_fd(file, 2);
	}
	return (ret);
}

void	get_fds(t_data *list)
{
	char	**full_cmd;
	int		i;

	full_cmd = list->directions;
	i = 0;
	if (!full_cmd)
		return ;
	while (full_cmd[i])
	{
		if (ft_strcmp(full_cmd[i], ">") == 0)
		{
			i++;
			if (list->out_fd != 0)
				close(list->out_fd);
			list->out_fd = open_file(full_cmd[i], 1);
		}
		else if (ft_strcmp(full_cmd[i], "<") == 0)
		{
			i++;
			if (list->in_fd != 0)
				close(list->in_fd);
			list->in_fd = open_file(full_cmd[i], 0);
		}
		else if (ft_strcmp(full_cmd[i], ">>") == 0)
		{
			i++;
			if (list->out_fd != 0)
				close(list->out_fd);
			list->out_fd = open_file(full_cmd[i], 2);
		}
		else if (ft_strcmp(full_cmd[i], "<>") == 0)
		{
			i++;
			close(open_file(full_cmd[i], 1));
		}
		i++;

	}
}
