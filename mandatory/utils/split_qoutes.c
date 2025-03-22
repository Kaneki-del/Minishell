/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:48:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/21 22:37:22 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// shoud take a looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooook

size_t words_count(const char *s, char c) // This name 's'
{
    size_t count = 0;
    int in_quote = 0;
    char quote = 0;
    size_t i = 0;

    while (s[i]) {
        while ((s[i] == c || s[i] == '\t') && !in_quote) // Added '\t' check
            i++;
        if (!s[i])
            break;
        count++;
        while (s[i] && (in_quote || (s[i] != c && s[i] != '\t'))) { // Added '\t' check
            if (s[i] == '\'' || s[i] == '"') {
                if (!in_quote) {
                    in_quote = 1;
                    quote = s[i];
                }
                else if (s[i] == quote) {
                    in_quote = 0;
                    quote = 0;
                }
            }
            i++;
        }
    }
    return (count);
}

static char *store_next_word(const char *s, size_t *i, char c, t_gc **g_collector)
{
    size_t start;
    size_t len = 0;
    int in_quote = 0;
    char quote = 0;

    while (s[*i] == c || s[*i] == '\t') // Added '\t' check
        (*i)++;

    start = *i;
    while (s[*i] && (in_quote || (s[*i] != c && s[*i] != '\t'))) { // Added '\t' check
        if (s[*i] == '\'' || s[*i] == '"')
        {
            if (!in_quote)
            {
                in_quote = 1;
                quote = s[*i];
            }
            else if (s[*i] == quote)
            {
                in_quote = 0;
                quote = 0;
            }
        }
        (*i)++;
        len++;
    }
    char *word = gc(len + 1, g_collector);
    if (!word)
        return (NULL);
    ft_strlcpy(word, s + start, len + 1);
    return (word);
}

char **ft_split(char const *s, char c, t_gc **g_collector)
{
  char **p;
  size_t i;
  size_t j;

  if (!s)
    return (NULL);
  p = gc((words_count(s, c) + 1) * sizeof(char *), g_collector);
  if (!p)
    return (NULL);
  i = 0;
  j = 0;
  while ((words_count(s, c)) > j) {
    p[j] = store_next_word(s, &i, c, g_collector);
    if (!(p[j]))
      return (NULL);
    j++;
  }
  p[j] = NULL;
  return (p);
}
