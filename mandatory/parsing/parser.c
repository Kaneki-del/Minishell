#include "../../includes/minishell.h"

t_token *init_data(t_token *token, char **dir_files, char **only_command, t_gc **g_collector)
{
	// free(*only_command);
	*only_command = NULL;
	// free(*dir_files);
	*dir_files = NULL;
	while (token && token->token_type != T_PIPE)
	{
		// get input and output directions as a string and files type
		get_dir_files(dir_files, token, g_collector);
		// get only command and there options as a single string
		get_command(only_command, token, g_collector);
		token = token->next;
	}
	// stop the loop at every pipe to consider all between pipes as single
	// separated node
	if (token && token->token_type == T_PIPE && token->next)
		return (token->next);
	return (NULL);
}

int parser(t_container *content)
{
	t_token *iter;
	char *dir_files;
	char *only_command;
	char *old_command;
	char **cmd_options;

	if (!content)
		return (0);
	dir_files = NULL;
	only_command = NULL;
	cmd_options = NULL;
	iter = content->tokens;
	content->flag = 1;
	while (iter)
	{
		iter = init_data(iter, &dir_files, &only_command, &content->g_collector);
		old_command = only_command;
		expanding_cmds_redirections(content, &only_command, &dir_files, 0);
		if (content->flag == 0)
			return (0);
		cmd_options = prepare_commands(&only_command, old_command, cmd_options, content);
		add_data_back(&content->data, new_data_node(old_command, cmd_options, filterd(ft_split(dir_files, ' ', \
		&content->g_collector), &content->g_collector), &content->g_collector));
	}
	return (1);
}

int parsing_case(t_container *content)
{
	// split all the command line by four sings "< |>" and initial them in linked
	// list in shape of tokens
	if (tokener(content) == 0)
		return (0);
	if (token_checker(content) == 0)
		return (0);
	// in parser fuction ill deal with all data amoung the pipes
	if (parser(content) == 0)
		return (0);
	return (1);
}
