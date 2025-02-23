#include "../../includes/minishell.h"

int token_split(t_container *content, int *i)
{
    if (content->line[(*i)] != '\0' && (ft_strchr("<|>", content->line[(*i)]) && (content->line[(*i) + 1] == '\0' || content->line[(*i) + 1] == '\n')))
        return (ft_error("bash: syntax error near unexpected token", "newline", 2, &content->g_collector), 0);
    else if (content->line[0] == '|' || (content->line[(*i)] == '|' && content->line[(*i) + 1] == '\0'))
        return (ft_error("bash: syntax error near unexpected token", "|", 2, &content->g_collector), 0);
    else if (content->line[(*i)] == '<' && content->line[(*i) + 1] == '<')
    {
        ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup("<<", &content->g_collector), T_REDIRECTE_HEREDOC, &content->g_collector));
        (*i)++;
    }
    else if (content->line[(*i)] == '>' && content->line[(*i) + 1] == '>')
    {
        ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup(">>", &content->g_collector), T_REDIRECTE_APPEND, &content->g_collector));
        (*i)++;
      }
    else if (content->line[(*i)] == '<')
        ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup("<", &content->g_collector), T_REDIRECTE_IN, &content->g_collector));
    else if (content->line[(*i)] == '>')
    {
        ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup(">", &content->g_collector), T_REDIRECTE_OUT, &content->g_collector));
        if (content->line[(*i) + 1] == '|')
            (*i)++;
    }
    else if (content->line[(*i)] == '|')
        ft_lstadd_back(&content->tokens, ft_lstnew(ft_strdup("|", &content->g_collector), T_PIPE, &content->g_collector));
    return (1);
}

int skeep_special_char(t_container *content, int *start)
{
    int is_in;
    char qoute;

    is_in = 0;
    while (content->line[(*start)] && !ft_strchr("<|>", content->line[(*start)]) && !ft_strchr(" \n\t", content->line[(*start)]))
    {
        if (content->line[(*start)] == '\'' || content->line[(*start)] == '"')
        {
            qoute = content->line[(*start)];
            ((*start)++, is_in = 1);
            while (content->line[(*start)] && content->line[(*start)] != qoute)
                (*start)++;
            if (content->line[(*start)] == qoute)
                ((*start)++, is_in = 0);
        }
        while (content->line[(*start)] && (content->line[(*start)] != '\'' && content->line[(*start)] != '"') && \
        !ft_strchr("<|>", content->line[(*start)]) && !ft_strchr(" \n\t", content->line[(*start)]))
            (*start)++;
    }
    if (is_in == 1)
        return (ft_error("bash: syntax error near unexpected token", &qoute, 2, &content->g_collector), 0);
    return (1);
}

int tokener(t_container *content)
{
    int i;
    int start;
    char *word;

    i = -1;
    if (!content->line)
      return (0);
    while (content->line[++i]) {
        if (ft_strchr(" \n\t", content->line[i]))
            continue ;
        if (token_split(content, &i) == 0)
            return (0);
        if (content->line[i] && !ft_strchr("<|>", content->line[i]) && !ft_strchr(" \n\t", content->line[i]))
        {
            start = i;
            if (skeep_special_char(content, &start) == 0)
                return (0);
            word = gc(start - i + 1, &content->g_collector);
            ft_strlcpy(word, &content->line[i], start - i + 1);
            ft_lstadd_back(&content->tokens, ft_lstnew(word, T_WORD, &content->g_collector));
            i = start - 1;
        }
    }
    return (1);
}

// int tokener(t_token **token, t_gc **g_collector, char *s_part) {
//     int i;
//     int start;
//     int is_in;
//     char *word;
//     char qoute;

//     i = -1;
//     is_in = 0;
//     if (!s_part)
//       return (0);
//     while (s_part[++i]) {

//       if (ft_strchr(" \n\t", s_part[i]))
//         continue;
//       else if ((ft_strchr("<|>", s_part[i]) && s_part[i + 1] == '\0') || (s_part[0] == '|'))
//         return (ft_error("bash: syntax error near unexpected token", s_part[i], 2, g_collector), 0);
//       else if (s_part[i] == '<' && s_part[i + 1] == '<') {
//         ft_lstadd_back(token, ft_lstnew(ft_strdup("<<", g_collector), T_REDIRECTE_HEREDOC, g_collector));
//         i++;
//       } else if (s_part[i] == '>' && s_part[i + 1] == '>') {
//         ft_lstadd_back(token, ft_lstnew(ft_strdup(">>", g_collector), T_REDIRECTE_APPEND, g_collector));
//         i++;
//       } else if (s_part[i] == '<')
//         ft_lstadd_back(token, ft_lstnew(ft_strdup("<", g_collector), T_REDIRECTE_IN, g_collector));
//       else if (s_part[i] == '>')
//         ft_lstadd_back(token, ft_lstnew(ft_strdup(">", g_collector), T_REDIRECTE_OUT, g_collector));
//       else if (s_part[i] == '|')
//         ft_lstadd_back(token, ft_lstnew(ft_strdup("|", g_collector), T_PIPE, g_collector));
//       else if (s_part[i] == '\\' && ft_strchr("<|>", s_part[i + 1])) {
//         ft_lstadd_back(token, ft_lstnew(ft_chrjoin('\\', s_part[i + 1], g_collector), T_WORD, g_collector));
//         i++;
//       }
//       else
//       {
//         start = i;
//         while (s_part[start] && !ft_strchr("<|>", s_part[start]) &&
//               !ft_strchr(" \n\t", s_part[start])) {
//           if (s_part[start] == '\'' || s_part[start] == '"') {
//             qoute = s_part[start];
//             start++;
//             is_in = 1;
//             while (s_part[start] && s_part[start] != qoute)
//               start++;
//             if (s_part[start] == qoute)
//             {
//               start++;
//               is_in = 0;
//             }
//           }
//           while (s_part[start] &&
//                 (s_part[start] != '\'' && s_part[start] != '"') &&
//                 !ft_strchr("<|>", s_part[start]) &&
//                 !ft_strchr(" \n\t", s_part[start]))
//             start++;
//         }
//         // check for qoutations if are closed
//         if (is_in == 1)
//           return (ft_error("bash: syntax error near unexpected token", qoute, 2, g_collector), 0);
//         word = gc(start - i + 1, g_collector);
//         if (!word)
//           return (ft_error("bash: cannot allocate memory for token",s_part[start], 2, g_collector), 0);
//         ft_strlcpy(word, &s_part[i], start - i + 1);
//         ft_lstadd_back(token, ft_lstnew(word, T_WORD, g_collector));
//         i = start - 1;
//       }
//     }
//     return (1);
// }
