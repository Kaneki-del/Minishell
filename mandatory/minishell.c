/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:20:31 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/15 12:59:31 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void tokener(t_token **token, char *s_part)
{
    int i;
    int start;
    char *word;
    char *spaces;
    char qoute;
    int  in_qoute;
    
    i = -1;
    in_qoute = 0;
    spaces = " \n\t";
    while (s_part[++i])
    {
        if (ft_strchr(spaces, s_part[i]))
            continue ;
        else if (s_part[i] == '<' && s_part[i + 1] == '<')
        {
            ft_lstadd_back(token, ft_lstnew(ft_strdup("<<"), T_REDIRECTE_HEREDOC));
            i++;
        }
        else if (s_part[i] == '>' && s_part[i + 1] == '>')
        {
            ft_lstadd_back(token, ft_lstnew(ft_strdup(">>"), T_REDIRECTE_APPEND));
            i++;
        }
        else if (s_part[i] == '<')
            ft_lstadd_back(token, ft_lstnew(ft_strdup("<"), T_REDIRECTE_IN));
        else if (s_part[i] == '>')
            ft_lstadd_back(token, ft_lstnew(ft_strdup(">"), T_REDIRECTE_OUT));
        else if (s_part[i] == '|')
            ft_lstadd_back(token, ft_lstnew(ft_strdup("|"), T_PIPE));
        else 
        {
            start = i;
            while (s_part[start] && !ft_strchr("<|>", s_part[start]) && !ft_strchr(spaces, s_part[start]))
            {
                if (s_part[start] == '\'' || s_part[start] == '"')
                {
                    qoute = s_part[start];
                    in_qoute = 1;
                    start++;
                    while (s_part[start] && s_part[start] != qoute)
                        start++;
                    if (s_part[start] == qoute)
                        (start++, in_qoute = 0);
                }
                while (s_part[start] && (s_part[start] != '\'' && s_part[start] != '"') && \
                !ft_strchr("<|>", s_part[start]) && !ft_strchr(spaces, s_part[start]))
                    start++;
            }
            // check for qoutations if are closed 
            if (in_qoute == 1)
                printf("bash : qoutations error `%c`\n", qoute); // shoud stop here 
            word = (char *)malloc(sizeof(char *) * (start - i + 1));
            if (!word)
                exit(EXIT_FAILURE);
            ft_strlcpy(word, &s_part[i], start - i + 1);
            ft_lstadd_back(token, ft_lstnew(word, T_WORD));
            i = start - 1;
        }
    }
} 

void get_dir_files(char **dir_files, t_token *token)
{
    if (!token || !token->next)
        return ;
    if ((token->token_type == T_REDIRECTE_IN || token->token_type == T_REDIRECTE_HEREDOC) && \
    token->token_type != T_PIPE)
    {
       *dir_files = ft_strjoin(*dir_files, token->value);
       *dir_files = ft_strjoin(*dir_files, " ");
       *dir_files = ft_strjoin(*dir_files, token->next->value);
       *dir_files = ft_strjoin(*dir_files, " ");
    }
    else if ((token->token_type == T_REDIRECTE_OUT || token->token_type == T_REDIRECTE_APPEND) && \
    token->token_type != T_PIPE)
    {
       *dir_files = ft_strjoin(*dir_files, token->value);
       *dir_files = ft_strjoin(*dir_files, " ");
       *dir_files = ft_strjoin(*dir_files, token->next->value);
       *dir_files = ft_strjoin(*dir_files, " ");
    }
}

void get_command(char **only_command, t_token *token)
{
    static int input_check;
    static int output_check;
    
    // apply a check for all the redirections and files skeep them and make sure to get only 
    // the command no mutter if they are behinde the input or output redirection sing
    if (token->token_type == T_REDIRECTE_OUT || token->token_type == T_REDIRECTE_APPEND)
        output_check = 1;
    else if (token->token_type == T_REDIRECTE_IN || token->token_type == T_REDIRECTE_HEREDOC)
        input_check = 1;
    else if (token->token_type == T_WORD && (input_check == 1 || output_check == 1 ))
        (input_check = 0, output_check = 0);
    else if (token->token_type == T_WORD && (input_check == 0 || output_check == 0))
    {
        *only_command = ft_strjoin(*only_command, " ");
        *only_command = ft_strjoin(*only_command, token->value);
    }
}

t_token *init_data(t_token *token, char **dir_files, char **only_command)
{
    while (token && token->token_type != T_PIPE)
    {
        // get input and output directions as a string and files type
        get_dir_files(dir_files, token);
        // get only command and there options as a single string
        get_command(only_command, token);
        token = token->next;
    }
    // stop the loop at every pipe to consider all between pipes as single separated node
    if (token && token->token_type == T_PIPE && token->next)
        return (token->next);
    return (NULL);
}

char *filer_qoutations(char *command_line)
{
    int i;
    int j;
    int in_qoute;
    char qoute;
    char *words_between;

    in_qoute = 0;
    j = 0;
    i = 0;
    if (!command_line)
        return (NULL);
    words_between = malloc(ft_strlen(command_line) + 1);
    if (!words_between)
        return (NULL);// shoud handle 
    while (command_line[i])
    {
        if ((command_line[i] == '"' || command_line[i] == '\'' ) && !in_qoute)
        {
            qoute = command_line[i];
            (in_qoute = 1, i++);
        }
        else if (command_line[i] == qoute && in_qoute)
            (in_qoute = 0, i++);
        else
            words_between[j++] = command_line[i++];
    }
    words_between[j] = '\0';
    free(command_line);
    return (words_between);
}
void parser(t_token **token, t_data **data)
{
    t_token *iter;
    char *dir_files;
    char *only_command;

    dir_files = NULL;
    only_command = NULL;
    iter = *token;
    while (iter)
    {
        // loop until |
        iter = init_data(iter, &dir_files, &only_command);

        // filter beside or secounded qoutes
        only_command = filer_qoutations(only_command);

        // split redirections and command (with options) and pass them to creat a new node (general structer) than add the node at the end of list
        add_data_back(data, new_data_node(ft_split(only_command, ' '), ft_split(dir_files, ' ')));
    }
}

void ft_free_tokens(t_token **token)
{
    t_token *hold;
    t_token *iter;

    iter = NULL;
    iter = *token;
    while (iter)
    {
        hold = iter->next;
        free(iter->value);
        free(iter);
        iter = hold;
    }
    *token = NULL;
}

// typedef struct s_token
// {
//     char *value;
//     int index;
//     t_type_token token_type;
//     struct s_token *next;
// } t_token;

void parsing_case(t_token **tokens, t_data **data, char *line)
{
    // split all the command line by four sings "< |>" and initial them in linked list in shape of tokens
    tokener(tokens, line);
    // in parser fuction ill deal with all data amoung the pipes
    parser(tokens, data);
}

// void print_tokens(t_token **tokens)
// {
//     t_token *hold;

//     hold = *tokens;
//     while (hold)
//     {
//         printf("  %s\n", hold->value);
//         hold = hold->next;
//     }
// }

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;

    char *line;
    t_token *tokens;
    t_data *data;
    if (ac != 1)
        return (1);
    tokens = NULL;
    data = NULL;
    while (1)
    {
        line = readline("\033[2;34mshell$> \033[0m");
        if (!line)
            exit(EXIT_SUCCESS);
        if (line[0] != '\0')
            add_history(line);
        //this function contains all paring cases
        parsing_case(&tokens, &data, line);
        
        // print_tokens(&tokens);
        free(line);
        ft_free_tokens(&tokens);
    }
    return (0);
}