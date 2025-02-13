/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:20:31 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/13 11:54:05 by kben-tou         ###   ########.fr       */
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
    
    i = -1;
    spaces = " \n\t";
    while (s_part[++i])
    {
        if (ft_strchr(spaces, s_part[i]))
            continue ;
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
                    start++;
                    while (s_part[start] && s_part[start] != qoute)
                        start++;
                    if (s_part[start] == qoute)
                        start++;
                }
                while (s_part[start] && (s_part[start] != '\'' && s_part[start] != '"') && \
                !ft_strchr("<|>", s_part[start]) && !ft_strchr(spaces, s_part[start]))
                    start++;
            }
            word = (char *)malloc(sizeof(char *) * (start - i + 1));
            if (!word)
                exit(EXIT_FAILURE);
            ft_strlcpy(word, &s_part[i], start - i + 1);
            ft_lstadd_back(token, ft_lstnew(word, T_WORD));
            i = start - 1;
        }
    }
}

t_token *to_one(t_token *token, t_token *de_token, t_type_token type)
{
    if (!token || !token->next || !de_token)
        return (NULL);
    t_token *tmp;
    token->value = ft_strjoin(token->value, token->next->value);
    if (!token->value)
        return (NULL);
    tmp = token->next->next;
    free(token->next->value);
    free(token->next);
    token->next = tmp;
    token->token_type = type;
    return (token);
}

void joiner(t_token **token)
{
    t_token *iter;

    iter = *token;
    while (iter && iter->next)
    {
        if (ft_strncmp(iter->value, "<", 2) == 0 && \
        ft_strncmp(iter->next->value, "<", 2) == 0)
            iter = to_one(iter, iter->next, T_REDIRECTE_HEREDOC);
        else if (ft_strncmp(iter->value, ">", 2) == 0 && \
        ft_strncmp(iter->next->value, ">", 2) == 0)
            iter = to_one(iter, iter->next, T_REDIRECTE_APPEND);
        iter = iter->next;
    }
}


// t_token *init_data(t_token *token)
// {
//     char *inname;
//     char *outname;
//     char *command;

//     command = NULL;
//     inname = NULL;
//     outname = NULL;
//     while (token && ft_strncmp(token->value, "|", 2) != 0)
//     {
//         // init_data()
//         // check_input_file();
//         // check_output_file();
//         if (token->next && ft_strncmp(token->value, "<", 2) == 0)
//             inname = ft_strdup(token->next->value);
//         else if (token->next && ft_strncmp(token->value, ">", 2) == 0)
//             outname = ft_strdup(token->next->value);
//         token = token->next;
//     }
//     printf("(%s)\n", inname);
//     printf("(%s)\n", outname);
//     if (token && ft_strncmp(token->value, "|", 2) == 0 && token->next)
//         return (token->next);
//     return (NULL);
// }

void get_dir_files(char **dir_files, t_type_token *input_type, t_type_token *output_type,t_token *token)
{
    if (!token || !token->next)
        return ;
    if (ft_strncmp(token->value, "<", 2) == 0 || ft_strncmp(token->value, "<<", 3) == 0)
    {
        *dir_files = ft_strjoin(*dir_files, token->value);
        *dir_files = ft_strjoin(*dir_files, " ");
        *dir_files = ft_strjoin(*dir_files, token->next->value);
        *dir_files = ft_strjoin(*dir_files, " ");
        if (ft_strncmp(token->value, "<", 2) == 0)
            *input_type = T_REDIRECTE_IN;
        else
            *input_type = T_REDIRECTE_HEREDOC;
    }
    else if (ft_strncmp(token->value, ">", 2) == 0 || ft_strncmp(token->value, ">>", 3) == 0)
    {
        *dir_files = ft_strjoin(*dir_files, token->value);
        *dir_files = ft_strjoin(*dir_files, " ");
        *dir_files = ft_strjoin(*dir_files, token->next->value);
        *dir_files = ft_strjoin(*dir_files, " ");
        if (ft_strncmp(token->value, ">", 2) == 0)
            *output_type = T_REDIRECTE_OUT;
        else
            *output_type = T_REDIRECTE_APPEND;
    }
}

t_token *init_data(t_token *token)
{
    char *dir_files;
    t_type_token input_type;
    t_type_token output_type;

    dir_files = NULL;
    while (token && ft_strncmp(token->value, "|", 2) != 0)
    {
        // check_input_file(); 
        // check_out_file();
        get_dir_files(&dir_files, &input_type, &output_type ,token);
        // printf(" %d(%s) ",token->index, token->value);
        token = token->next;
    }
    printf("[%d]- {%d} - (%s)\n", input_type, output_type, dir_files);
    if (token && ft_strncmp(token->value, "|", 2) == 0 && token->next)
        return (token->next);
    return (NULL);
}

void parser(t_token **token, t_data **data)
{
    t_token *iter;

    iter = *token;
    (void)data;
    while (iter)
    {
        // init_data()
        iter = init_data(iter);
        printf("\n");
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
    tokener(tokens, line);
    joiner(tokens);
    parser(tokens, data);
}

void f()
{
    system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    
    char *line;
    char cwd[PATH_MAX];
    t_token *tokens;
    t_data *data;
    atexit(f);
    // printf("%s\n",ft_split("'hello this is'", ' ')[0]);
    // exit(0);
    if (ac != 1)
        return (1);
    getcwd(cwd, sizeof(cwd));
    tokens = NULL;
    while (1)
    {
        line = readline("\033[2;34mshell$> \033[0m");
        if (!line)
            exit(EXIT_SUCCESS);
        if (line[0] != '\0')
            add_history(line);
        parsing_case(&tokens, &data, line);
        free(line);
        ft_free_tokens(&tokens);
    }
    return (0);
}