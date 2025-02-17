#include "../../includes/minishell.h"
/* char *ft_substr(char const *s, unsigned int start, size_t len) { */
/*   size_t i; */
/*   char *str; */
/**/
/*   if (!s) */
/*     return (NULL); */
/*   if (len > ft_strlen(s) - start) */
/*     len = ft_strlen(s) - start; */
/*   if (start >= ft_strlen(s)) */
/*     return (ft_strdup("")); */
/*   i = 0; */
/*   str = (char *)malloc(len + 1); */
/*   if (str == NULL) */
/*     return (NULL); */
/*   while (i < len) { */
/*     str[i] = s[start + i]; */
/*     i++; */
/*   } */
/*   str[i] = '\0'; */
/*   return (str); */
/* } */
/**/
#include <stdio.h>
void print_tab(char **str) {
  int i = 0;
  printf("->%s\n", str[i]);
  i++;
  if (str[i] == NULL)
    printf("i am here\n");
  i++;
}
char **ft_split_equal_to(const char *s) {
  if (s == NULL)
    return NULL;

  char **str =
      (char **)malloc(sizeof(char *) * 3); // Two substrings + NULL terminator
  if (str == NULL)
    return NULL;

  size_t len = ft_strlen(s);
  size_t j = 0;

  // Find the first '=' or end of string
  while (s[j] != '=' && s[j] != '\0')
    j++;

  // If '=' is found, split key and value
  if (s[j] == '=') {
    str[0] = ft_substr(s, 0, j);           // Copy key
    str[1] = ft_substr(s, j + 1, len - j); // Copy value
  } else {
    str[0] = ft_strdup(s); // No '=', just copy the entire string as key
    str[1] = NULL;         // No value, set the second part to NULL
  }

  str[2] = NULL; // Null-terminate the array
  return str;
}

int main() {
  char *str = "VALUE";
  char **sp = ft_split_equal_to(str);
  print_tab(sp);
}
