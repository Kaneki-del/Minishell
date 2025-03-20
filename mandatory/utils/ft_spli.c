/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spli.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:48:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/20 15:39:47 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t wordc(const char *s, char c) {
    size_t count = 0;
    size_t i = 0;

    while (s[i]) {
        if (s[i] == c || s[i] == '\t') // Treat delimiters (c and '\t') as separate words
            count++;
        else if (s[i]) {
            count++;
            while (s[i] && (s[i] != c && s[i] != '\t'))
                i++;
            continue;
        }
        i++;
    }
    return count;
}

static char *store_ne(const char *s, size_t *i, char c, t_gc **g_collector) {
    size_t start = *i;
    size_t len = 0;

    // Check if it's a delimiter
    if (s[*i] == c || s[*i] == '\t') {
        len = 1; // Single delimiter as a word
        (*i)++;
    } else {
        while (s[*i] && (s[*i] != c && s[*i] != '\t')) {
            (*i)++;
            len++;
        }
    }

    char *word = gc(len + 1, g_collector); // Allocate space for the word
    if (!word)
        return NULL;
    ft_strlcpy(word, s + start, len + 1);
    return word;
}

char **ft_spl(const char *s, char c, t_gc **g_collector) {
    char **p;
    size_t i = 0, j = 0;

    if (!s)
        return NULL;
    p = gc((wordc(s, c) + 1) * sizeof(char *), g_collector);
    if (!p)
        return NULL;

    while (s[i]) {
        p[j] = store_ne(s, &i, c, g_collector);
        if (!p[j])
            return NULL;
        j++;
    }
    p[j] = NULL;
    return p;
}


// char **ft_split(char const *s, char c, t_gc **g_collector) {
//     char **result;
//     size_t word_count;
//     size_t i = 0;
//     size_t j = 0;

//     if (!s)
//         return (NULL);
    
//     word_count = wordc(s, c);
//     result = gc((word_count + 1) * sizeof(char *), g_collector);
//     if (!result)
//         return (clear_bin(g_collector), NULL);
    
//     while (j < word_count) {
//         result[j] = store_next_word(s, &i, c, g_collector);
//         if (!result[j]) {
//             clear_bin(g_collector);
//             return (NULL);
//         }
//         j++;
//     }
//     result[j] = NULL;
//     return (result);
// }

// static size_t wordc(const char *s, char c) {
//   size_t i;
//   size_t count;
//   char quote;

//   i = -1;
//   count = 0;
//   quote = 0;
//   while (s[++i]) {
//     if (s[i] == '\'' || s[i] == '"') {
//       count++;
//       quote = s[i];
//       while (s[++i] && s[i] != quote)
//         ;
//       if (s[i] == quote)
//         i++;
//       quote = 0;
//     } else if (s[i] != c && (i == 0 || s[i - 1] == c) && !quote)
//       count++;
//   }
//   return (count);
// }

// // static void mem_free(char **p) {
// //   size_t i;

// //   i = 0;
// //   while (p[i]) {
// //     free(p[i]);
// //     i++;
// //   }
// //   free(p);
// // }

  
