#include "../../includes/minishell.h"

char *remove_quotes(char *command, t_gc **g_collector)
{
    char *res;
    int i;
    int j;
    char current_quote;

    current_quote = '\0';
    j = 0;
    i = 0;
    if (!command) 
        return (NULL);
    res = gc(ft_strlen(command) + 1, g_collector);
    if (!res) 
        return (NULL);
    while (command[i])
    {
        if (current_quote == '\0' && (command[i] == '\'' || command[i] == '"'))
            current_quote = command[i++];
        else if (current_quote && command[i] == current_quote)
        {
            current_quote = '\0';
            i++;
        }
        else
            res[j++] = command[i++];
    }
    res[j] = '\0';
    return res;
}

void ft_print2(char **str)
{
  int i;

  i = 0;
  if (!str)
    return ;
  while (str[i])
  {
    printf("(%s)\n", str[i]);
    i++;  
  }
}

char **filter_all(char **cmds, t_gc **g_collector)
{
    int i;

    i = 0;
    if (!cmds)
        return (NULL);
    while (cmds[i])
    {
        cmds[i] = remove_quotes(cmds[i], g_collector);
        i++;
    }
    return (cmds);
}

int get_char_index(char *s, char c)
{
    int i = 0;
    int store = 0;
    char qoute;
    int is_in;

    is_in = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'' )
        {
            if (is_in == 0 )
            {
                is_in = 1;
                qoute = s[i];
            }
            else if (is_in == 1 && qoute == s[i])
                is_in = 0;
        }
        if (s[i] == c && !is_in)
            store = i;
        i++;
    }
    return (store);
}

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
                if (cmd_options[1] && cmd_options[1][get_char_index(cmd_options[1], '=') + 1] == '"' && cmd_options[1][ft_strlen(cmd_options[1]) - 1] == '"')
                    *only_command = remove_quotes(*only_command, &content->g_collector);
                cmd_options = ft_split(*only_command, ' ', &content->g_collector);
                if (cmd_options[1])
                {
                    cmd_options[1] = ft_strdup(*only_command + 7, &content->g_collector); 
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
		cmd_options = normal_ft_split(*only_command, ' ', &content->g_collector);
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
    {
        if (content->flag == 5)
            cmd_options = ft_split(*only_command, ' ', &content->g_collector);
        else
		    cmd_options = filter_all(ft_split(*only_command, ' ', &content->g_collector), &content->g_collector);
    }
    // char **old = ft_split(old_cmd, ' ', &content->g_collector);
	cmd_options = check_echo_options(cmd_options, &content->g_collector);
	return (cmd_options);
}

void expanding_cmds_redirections(t_container *content, char **only_command, char **dir_files, int shoud_skeep) //export a="echo sdf"   export k="export $a"
{
	if (only_command && *only_command)
	{
		content->flag = 2;
		*only_command = check_env_var(content, *only_command, shoud_skeep);
	}
	if (dir_files && *dir_files)
	{
		content->flag = 1;
		*dir_files = check_env_var(content, *dir_files, shoud_skeep);
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