#include "../../includes/minishell.h"

char single_qoutes(char c)
{
    static int is_in;
    static char qoute;

    if (c == '\'')
    {
        if (!is_in)
        {
            is_in = 1;
            qoute = c;
        }
        else if (is_in && c == qoute)
        {
            is_in = 0;
            qoute = '\0';
        }
    }
    return (qoute);
}

char double_qoutes(char c)
{
    static int is_in;
    static char qoute;

    if (c == '"')
    {
        if (!is_in)
        {
            is_in = 1;
            qoute = c;
        }
        else if (is_in && c == qoute)
        {
            is_in = 0;
            qoute = '\0';
        }
    }
    return (qoute);
}

char *exit_status(t_container *content, int *i)
{
    char *res;

    if (!content)
        return (NULL);
    (*i)++;
    res = ft_itoa(content->status, &content->g_collector);
    if (!res)
        return (NULL);
    return (res);
}


char *expand_telda(char *command, int *i, t_env **env_list)
{
    t_env *pair;

    pair = NULL;
    if (command[(*i)] == '~' && ((command[(*i) + 1] == ' ' || command[(*i) + 1] == '\0' || command[(*i) + 1] == '/') && ((*i) == 0 || command[(*i) - 1] == ' ' || (ft_strncmp(command, "export ", 7) == 0 && command[(*i) - 1] == '='))))
    {
        (*i)++;
        pair = check_if_there("HOME", env_list);
        if (!pair)
            return (NULL);
        return (pair->value);
    }
    return (NULL);
}

int check_double(char *command, int i, char qoute)
{
    if (command[i] == '$' && qoute)
    {
        i++;
        while (command[i] == ' ' || command[i] == '\t')
            i++;
        if (command[i] == qoute)
            return (0);
    }
    return (1);
}

char *add_qoutations(char *command, t_gc **g_collector)
{
  int i;
  int j;
  char *res;

  i = 0;
  j = 1;
  if (check_is_in_qoutes(command))
      return (command);
  res = gc(ft_strlen(command) + 3, g_collector);
  res[0] = '"';
  while (command[i])
  {
    res[j] = command[i];
    i++;
    j++;
  }
  res[j] = '"';
  res[j + 1] = '\0';
  return (res);
}

char *expand(t_container *content, char *command, int *i, int *flag)
{
    t_env *pair;
    char *key;
    int start;
    // char qoute;

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
    if (!pair || pair->print_flag == 3)
    {
        if ((*flag) == 1)
        {
            ft_error_exec_two("bash: ", key, ": ambiguous redirect", 2);
            (*flag) = 0;
            content->status = 1;
        }
        return (ft_strdup("\0", &content->g_collector));
    }
    if (pair && (*flag) == 1 && pair->value && (words_count(filer_qoutations(pair->value, &content->g_collector), ' ') > 1))
    {
        ft_error_exec_two("bash: ", key, ": ambiguous redirect", 2);
        (*flag) = 0;
        content->status = 1;
        return (ft_strdup("\0", &content->g_collector));
    }
    *(flag) = 5;
    if (!pair->value)
        return (NULL);
    return (add_qoutations(pair->value, &content->g_collector));
}

// the first this is the epandable string shoud starts with $ and end with special character 
char *check_env_var(t_container *content, char *command, int *flag, int here_doc_flag)
{
    int i;
    char *new_command;
    char *curent_part;
    int is_in;
    char qoute;
    int inexpand_here;

    if (!command)
        return (NULL);
    i = 0;
    is_in = 0;
    new_command = NULL;
    curent_part = NULL;
    inexpand_here = 0;
    while (command[i])
    {
        if (command[i] == '\'' || command[i] == '"')
        {
            if (!is_in)
            {
                is_in = 1;
                qoute = command[i];
            }
            else if (is_in && command[i] == qoute)
            {
                is_in = 0;
                qoute = '\0';
            }
        }
        if (command[i] == '<' && command[i + 1] == '<' && !is_in)
            inexpand_here = 1;
        if (command[i] == '$' && (qoute != '\'' || here_doc_flag) && command[i + 1] != qoute && (ft_isalnum(command[i + 1]) || command[i + 1] == '\''  || command[i + 1] == '"' || command[i + 1] == '?' || command[i + 1] == '_'))
        {
            if (here_doc_flag)
            {
                if (ft_isalnum(command[i + 1]) || command[i + 1] == '?')
                {
                    while (command[i] == '$')
                        i++;
                    if (command[i] == '?')
                    {
                        i++;
                        new_command = ft_strjoin(new_command, ft_itoa(content->status, &content->g_collector), &content->g_collector);
                        continue;
                    }
                    else if (ft_isalnum(command[i]))
                    {
                        curent_part = expand(content, command, &i, flag);
                        if (curent_part)
                        {
                            new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
                            continue;
                        }
                    }
                }
            }
            else
            {
                if ((command[i] && qoute == '"' && command[i + 1] == '\'') || (inexpand_here && command[i + 1] != '\''  && command[i + 1] != '"' ))
                    ;
                else
                {
                    i++;
                    if (!ft_isalpha(command[i]) || qoute == '"')
                        (*flag) = 3;
                    if (command[i] == '?')
                    {
                        i++;
                        new_command = ft_strjoin(new_command, ft_itoa(content->status, &content->g_collector), &content->g_collector);
                        continue;
                    }
                    else if (((ft_isdigit(command[i]) || (!ft_isalpha(command[i]) && command[i] != '_')) && (command[i] != '"' && command[i] != '\'' )))
                        i++;
                    else if (ft_isalnum(command[i]) || command[i] == '_')
                    {
                        curent_part = expand(content, command, &i, flag);
                        if (curent_part)
                            new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
                        continue;
                    }

                }
            }
        }
        else if(qoute != '"' && qoute != '\'' && command[i] == '~' && !inexpand_here && !here_doc_flag)
        {
            curent_part = expand_telda(command, &i, &content->env_list);
            if (curent_part)
            {
                new_command = ft_strjoin(new_command, curent_part, &content->g_collector);
                continue;
            }
        }
        new_command = ft_strchr_join(new_command, command[i], &content->g_collector);
        i++;
    }
    return (new_command);
}

