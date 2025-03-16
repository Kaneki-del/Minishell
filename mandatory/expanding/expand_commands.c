#include "../../includes/minishell.h"

char** prepare_export_command(char **only_command, char **cmd_options, t_container *content)
{
	if(ft_strlen_2d(cmd_options) < 3)
	{
		if (cmd_options && cmd_options[1] && cmd_options[1][0] == '$')
			cmd_options = normal_ft_split(*only_command, ' ', &content->g_collector);
		else
		{
            if (ft_strcmp(cmd_options[0], "export") == 0)
            {
			    cmd_options = ft_split(*only_command, ' ', &content->g_collector);
                if (cmd_options[1])
                {
                    cmd_options[1] = filer_qoutations(ft_strdup(*only_command + 7, &content->g_collector),  &content->g_collector); 
                    cmd_options[2] = NULL;
                }
            }
            else
            {
		        cmd_options = ft_split(*only_command, ' ', &content->g_collector);
                cmd_options = prepare_export_command(only_command, cmd_options, content);
            }
		}
	}
	else
		cmd_options = filterd(normal_ft_split(*only_command, ' ', &content->g_collector), &content->g_collector);
	return (cmd_options);
}

char **prepare_commands(char **only_command, char *old_cmd ,char **cmd_options, t_container *content)
{
	if (!only_command || !*only_command)
		return (NULL);
	if (*only_command && ft_strncmp(*only_command, "export ", 7) == 0 && content->flag == 5)
	{
		cmd_options = ft_split(old_cmd, ' ', &content->g_collector);
        if (!cmd_options || !cmd_options[0])
            return (NULL);
		cmd_options = prepare_export_command(only_command, cmd_options, content);
	}
	else
		cmd_options = filterd(ft_split(*only_command, ' ', &content->g_collector), &content->g_collector);
	cmd_options = check_echo_options(cmd_options, &content->g_collector);
	return (cmd_options);
}

void expanding_cmds_redirections(t_container *content, char **only_command, char **dir_files) //export a="echo sdf"   export k="export $a"
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

int pair_check_cases(t_container *content, t_env *pair, char *key)
{
    if (!pair || !pair->value || pair->value[0] == '\0' || pair->print_flag == 3)
    {
        if (content->flag == 1)
        {
            ft_error_exec_two("mshell: ", key, ": ambiguous redirect", 2);
            content->flag = 0;
            content->status = 1;
        }
        return (1);
    }
    if (pair && content->flag == 1 && pair->value && \
    (words_count(filer_qoutations(pair->value, &content->g_collector), ' ') > 1))
    {
        ft_error_exec_two("mshell: ", key, ": ambiguous redirect", 2);
        content->flag = 0;
        content->status = 1;
        return (1);
    }
    return (0);
}

char *expand(t_container *content, char *command, int *i)
{
    t_env *pair;
    char *key;
    int start;

    pair = NULL;
    key = NULL;
    start = (*i);
    content->is_expandable = 1;
    while (command[start] && (ft_isalnum(command[start]) || command[start] == '_'))
        start++;
    key = gc(start - (*i) + 1, &content->g_collector);
    ft_strlcpy(key, &command[(*i)], start - (*i) + 1 );
    pair = check_if_there(key, &content->env_list);
    (*i) = start;
    if (pair_check_cases(content, pair, key) == 1)
        return (ft_strdup("\0", &content->g_collector));
    content->flag = 5;
    if (!pair->value)
        return (NULL);
    return (pair->value);
}