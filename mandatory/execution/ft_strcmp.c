#include "../../includes/minishell.h"
int ft_strcmp(const char *s1, const char *s2) {
  size_t i;

  i = 0;
  if (ft_strlen(s1) != ft_strlen(s2))
    return 1;
  while ((s1[i] || s2[i])) {
    if ((unsigned char)s1[i] != (unsigned char)s2[i])
      return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    i++;
  }
  return (0);
}
