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

static int check_is_last_redirection(t_token *iter, t_container *content)
{
	if (iter->next == NULL && (iter->token_type == T_PIPE || \
	iter->token_type == T_REDIRECTE_IN || iter->token_type == T_REDIRECTE_OUT \
	|| iter->token_type == T_REDIRECTE_APPEND || iter->token_type == T_REDIRECTE_HEREDOC))
	{
			content->status = 258;
			return (ft_error("bash: syntax error near unexpected token", "newline", 2), 0);
	}
	return (1);
}

static int check_is_pipe_first(t_token *iter, t_container *content, int flag)
{
	if (flag)
	{
		if (iter->token_type == T_PIPE)
		{
			content->status = 258;
			return (ft_error("bash: syntax error near unexpected token", "|", 2), 0);
		}
	}
	else
	{
		if (iter->token_type == T_PIPE && iter->next->token_type == T_PIPE)
		{
			content->status = 258;
			return (ft_error("bash: syntax error near unexpected token", iter->next->value, 2), 0);
		}
	}
	return (1);
}

int token_checker(t_container *content)
{
	t_token *iter;

	if (!content->tokens)
		return (0);
	iter = content->tokens;
	if (check_is_pipe_first(iter, content, 1) == 0)
		return (0);
	while (iter && iter->next)
	{
		if (check_is_pipe_first(iter, content, 0) == 0)
			return (0);
		if (redirection_pipe_check (iter, T_REDIRECTE_IN, content) == 0)
			return (0);
		if (redirection_pipe_check (iter, T_REDIRECTE_OUT, content) == 0)
			return (0);
		if (redirection_pipe_check (iter, T_REDIRECTE_APPEND, content) == 0)
			return (0);
		if (redirection_pipe_check (iter, T_REDIRECTE_HEREDOC, content) == 0)
			return (0);
		iter = iter->next;
	}
	if (check_is_last_redirection(iter, content) == 0)
		return (0);
	return (1);
}

char** prepare_export_command(char **only_command, char **cmd_options, t_container *content)
{
	if(ft_strlen_2d(cmd_options) < 3)
	{
		if (cmd_options[1][0] == '$')
		{
			cmd_options = normal_ft_split(*only_command, ' ', &content->g_collector);
			// cmd_options = filterd(cmd_options, &content->g_collector);
		}
		else
		{
			cmd_options[1] = filer_qoutations(ft_strdup(*only_command + 7, &content->g_collector),  &content->g_collector); 
			cmd_options[2] = NULL;
		}
	}
	else
		cmd_options = filterd(normal_ft_split(*only_command, ' ', &content->g_collector), &content->g_collector);
	return (cmd_options);
}

static char **prepare_commands(char **only_command, char *old_cmd ,char **cmd_options, t_container *content)
{
	if (!only_command || !*only_command)
		return (NULL);
	if (*only_command && ft_strncmp(*only_command, "export ", 7) == 0 && content->flag == 5)
	{
		cmd_options = ft_split(old_cmd, ' ', &content->g_collector);
		cmd_options = prepare_export_command(only_command, cmd_options, content);
	}
	else
	{
		cmd_options = filterd(ft_split(*only_command, ' ', &content->g_collector), &content->g_collector);
	}
	cmd_options = check_echo_options(cmd_options, &content->g_collector);
	return (cmd_options);
}

void expanding_cmds_redirections(t_container *content, char **only_command, char **dir_files)
{
	if (*only_command)
	{
		content->flag = 2;
		*only_command = check_env_var(content, *only_command);
	}
	if (*dir_files)
	{
		content->flag = 1;
		*dir_files = check_env_var(content, *dir_files);
	}
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
		expanding_cmds_redirections(content, &only_command, &dir_files);
		if (content->flag == 0)
			return (0);
		cmd_options = prepare_commands(&only_command, old_command, cmd_options, content);
		add_data_back(&content->data, new_data_node(cmd_options, filterd(ft_split(dir_files, ' ', \
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
