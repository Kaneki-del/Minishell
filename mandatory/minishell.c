/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:20:31 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/11 13:36:10 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

// void tokener(t_token **token, char *s_part)
// {
//     int i;
//     int start;
//     char *word;
//     int in_qoutes;
//     char qoute;
    
//     i = -1;
//     //"this " 'this one is''asd asdf adf' 
//     while (s_part[++i])
//     {
//         if (s_part[i] == '<')
//             ft_lstadd_back(token, ft_lstnew("<", T_REDIRECTE_IN));
//         else if (s_part[i] == '>')
//             ft_lstadd_back(token, ft_lstnew(">", T_REDIRECTE_OUT));
//         else if (s_part[i] == ' ')
//             printf("s");
//         else if (s_part[i] == '|')
//             ft_lstadd_back(token, ft_lstnew("|", T_PIPE));
//         else if (!ft_strchr("<|> ", s_part[i])) //"this"| "name"
//         {
//             start = i;
//             if (s_part[start] == '\'' || s_part[start] == '"')
//                 (1) && (in_qoutes = 1, qoute = s_part[start], start++);
//             if (in_qoutes)
//             {
//                 while (s_part[start] && s_part[start] != qoute)
//                     start++;
//                 if (s_part[start] == qoute)
//                     in_qoutes = 0;
//             }
//             else
//             {
//                 while (!ft_strchr("<|> ", s_part[start]))
//                     start++;
//             }
//             word = (char *)malloc((start - i + 1) * sizeof(char *));
//             if (!word)
//                 exit(EXIT_FAILURE);
//             ft_strlcpy(word, &s_part[i], start - i + 1);
//             ft_lstadd_back(token, ft_lstnew(word, T_WORD));
//             i = start;
//         }
//     }
// }

void tokener(t_token **token, char *s_part)
{
    int i;
    int start;
    char *word;
    int in_qoutes;
    char *spaces;
    char qoute;
    
    i = -1;
    spaces = " \n\t";
    while (s_part[++i])
    {
        if (s_part[i] == '<')
            ft_lstadd_back(token, ft_lstnew("<", T_REDIRECTE_IN));
        else if (s_part[i] == '>')
            ft_lstadd_back(token, ft_lstnew(">", T_REDIRECTE_OUT));
        else if (ft_strchr(spaces, s_part[i]))
            continue ;
        else if (s_part[i] == '|')
            ft_lstadd_back(token, ft_lstnew("|", T_PIPE));
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
                while (s_part[start] && (s_part[start] != '\'' && s_part[start] != '"') && !ft_strchr("<|>", s_part[start]) && !ft_strchr(spaces, s_part[start]))
                    start++;
            }
            word = (char *)malloc(sizeof(char *) * (start - i + 1));
            if (!word)
                exit(EXIT_FAILURE);
            ft_strlcpy(word, &s_part[i], start - i + 1);
            ft_lstadd_back(token, ft_lstnew(word, T_WORD));
            i = start;
        }
    }
}

// static void tokener(t_token **token, char *cmd_line) //  < infile ls    | echo "hello< | >">outfile
// {
//     int i;

//     i = 0;
//     (void)token;
//     while (cmd_line[i])
//     {
//         while ((cmd_line[i] == 32) || cmd_line[i] >= 9 && cmd_line[i] <= 13)
//             i++;
//         if (cmd_line[i] == '<')
//             printf("%c",cmd_line[i]);
//         else if (cmd_line[i] == '>')
//             ft_lstadd_back(token, ft_lstnew(">", T_REDIRECTE_OUT));
//         else if (cmd_line[i] == '|')
//             ft_lstadd_back(token, ft_lstnew("|", T_PIPE));
//         printf("%c\n", cmd_line[i]);
//         i++;
//     }
// }

// void lexser(t_token **token, char *line)
// {
//     char **s_whitespace;

//     s_whitespace = ft_split(line, ' ');
//     if (!s_whitespace)
//         exit(EXIT_FAILURE);
//     int i;

//     i = 0;
//     while (s_whitespace[i])
//     {
//         // ft_lstadd_back(token, ft_lstnew(splited_line[i]));
//         // tokener(token, s_whitespace[i]);
//         printf("%s\n", s_whitespace[i]);
//         i++;
//     }
// }


// void split_pipe_commands(char *line, t_data **data)
// {
//     char **piped_line;

//     (void)data;
//     piped_line = ft_split(line, '|');
//     if (!piped_line)
//         exit(EXIT_FAILURE);
//     int i;

//     i = 0;
//     while (piped_line[i] != NULL)
//     {
//         printf("%s\n", piped_line[i]);
//         i++;
//     }
// }

// void ft_free_tokens(t_token **token)
// {
//     t_token *ptr;

//     if (!token || !*token)
//         return ;

//     while (*token)
//     {   
//         ptr = *token;
//         *token = ptr->next;
//         free(ptr->value);
//         free(ptr);
//     }
// }


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    
    char *line;
    char cwd[PATH_MAX];
    t_token *tokens;
    t_data *data;

    // printf("%s\n",ft_split("'hello this is'", ' ')[0]);
    // exit(0);
    if (ac != 1)
        return (1);
    getcwd(cwd, sizeof(cwd));
    while (1)
    {
        line = readline("\033[2;34mshell$> \033[0m");
        if (!line)
            exit(EXIT_SUCCESS);
        if (line[0] != '\0')
            add_history(line);
        tokener(&tokens, line);
        while (tokens)
        {
            printf("%s\n", tokens->value);
            tokens=tokens->next;
        }
        // ft_free_tokens(&tokens);
    }

    return (0);
}