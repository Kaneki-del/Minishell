/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:20:31 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/12 15:04:15 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

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
            ft_lstadd_back(token, ft_lstnew("<", T_REDIRECTE_IN));
        else if (s_part[i] == '>')
            ft_lstadd_back(token, ft_lstnew(">", T_REDIRECTE_OUT));
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
    // if (!token || !de_token)
    //     return (NULL);
    t_token *tmp;
    token->value = ft_strjoin(token->value, token->next->value);
    if (!token->value)
        return (NULL);
    tmp = token->next->next;
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

// void parser(t_token **token)
// {
//     redirecter();
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
        joiner(&tokens);
        // parser(&tokens, data);
        while (tokens)
        {
            printf("%s          %d\n", tokens->value, tokens->token_type);
            tokens=tokens->next;
        }
        // ft_free_tokens(&tokens);
    }
    return (0);
}