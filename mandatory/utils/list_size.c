#include "../../includes/minishell.h"

int ft_lstsize(t_data *lst) {
  int size;

  size = 0;
  if (!lst)
    return (size);
  while (lst) {
    size++;
    lst = lst->next;
  }
  return (size);
}
