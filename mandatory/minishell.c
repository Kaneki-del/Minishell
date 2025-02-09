/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:20:31 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/09 16:40:33 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

void tokener(t_token **token, char *line)
{
    char **splited_line;

    splited_line = ft_split(line, ' ');
    if (!splited_line)
        exit(EXIT_FAILURE);
    int i;

    i = 0;
    while (splited_line[i])
    {
        // ft_lstadd_back(token, ft_lstnew(splited_line[i]));
        printf("%s\n", splited_line[i]);
        i++;
    }
}

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

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    
    char *line;
    char cwd[PATH_MAX];
    t_token *tokens;
    t_data *data;

    getcwd(cwd, sizeof(cwd));
    while (1)
    {
        line = readline("\033[2;34mshell$> \033[0m");
        if (!line)
            exit(EXIT_SUCCESS);
        // split_pipe_commands(line, &data);
        tokener(&tokens, line);
    }

    return (0);
}