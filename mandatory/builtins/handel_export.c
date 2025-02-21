
#include "../../includes/minishell.h"

t_env *copy_list(t_env *head) 
{
  if (!head)
    return NULL;
  t_env *new_head = lstnew_env(head->key, head->value);
  t_env *current_old = head->next;
  t_env *current_new = new_head;
  t_env *new_node;
  while (current_old) 
  {
    new_node = lstnew_env(current_old->key, current_old->value);
    current_new->next = new_node;
    current_new = new_node;
    current_old = current_old->next;
  }
  return new_head;
}

t_env *find_smallest(t_env *head) 
{
  if (!head)
    return NULL;
  t_env *smallest = head;
  t_env *current = head;
  while (current) {
    if (ft_strcmp(current->key, smallest->key) < 0) 
      smallest = current;
    
    current = current->next;
  }
  return smallest;
}
void delete_node(t_env **list_env, char *key) 
{
  t_env *temp = *list_env;
  t_env *prev = NULL;

  // Check if the first node is the one to delete
  if (temp && ft_strcmp(temp->key, key) == 0) 
  {
    *list_env = temp->next;
    return;
  }
  // Traverse the list to find the node to delete
  while (temp && ft_strcmp(temp->key, key) != 0)
  {
    prev = temp;
    temp = temp->next;
  }
  // If the node wasn't found, return
  if (!temp)
    return;
  // Unlink the node and free it
  prev->next = temp->next;
}
void print_export(t_env *env_list) 
{
  if (!env_list)
    return;
  t_env *temp = copy_list(env_list); // Start from the head
  t_env *smallest = NULL;
  while (temp) {
    smallest = find_smallest(temp); // Find the smallest element in the list
    if (!smallest)                  // Safety check
      return;
    // Print the key and value of the smallest element
    if (smallest->key && smallest->value)
      printf("declare -x %s=\"%s\"\n", smallest->key, smallest->value);
    else if (!smallest->value)
      printf("declare -x %s\n", smallest->key);

    // Delete the smallest node from the list
    delete_node(&temp, smallest->key); // Ensure temp is updated after deletion
  }
}
