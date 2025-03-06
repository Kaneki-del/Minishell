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

int her_doc(char *limiter, t_container *content)
{
	int fd;
	char *line;
	char *file_name;
	int fd2;
	int flag;

	flag = 0;
	file_name = get_file(&content->g_collector);
	fd = open_file(file_name, 1);
	fd2 = open_file(file_name, 0);
	unlink(file_name);
	while(1)
	{
		line = NULL;
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
				line = check_env_var(content, line, &flag, 1);
			write(fd, line,  ft_strlen(line));
			write(fd, "\n", 1); 
			line = NULL; // free line lead to a segfult
		}
	}
	close(fd);
	return fd2;
}