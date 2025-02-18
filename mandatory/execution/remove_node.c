
#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//->bb
//->cc
//->dd

void delete_node(t_env **list_env, char *key) {
  t_env *temp = *list_env;
  t_env *prev = NULL;

  // Check if the first node is the one to delete
  if (temp && strcmp(temp->key, key) == 0) {
    *list_env = temp->next;
    return;
  }

  // Traverse the list to find the node to delete
  while (temp && strcmp(temp->key, key) != 0) {
    prev = temp;
    temp = temp->next;
  }

  // If the node wasn't found, return
  if (!temp)
    return;

  // Unlink the node and free it
  prev->next = temp->next;
}
t_env *create_linked_list() {
  t_env *head;
  t_env *node2;
  t_env *node3;

  // Allocate and initialize the first node
  head = malloc(sizeof(t_env));
  head->key = ft_strdup("bb");
  head->value = NULL;
  head->next = NULL;

  // Allocate and initialize the second node
  node2 = malloc(sizeof(t_env));
  node2->key = ft_strdup("cc");
  node2->value = NULL;
  node2->next = NULL;
  head->next = node2;

  // Allocate and initialize the third node
  node3 = malloc(sizeof(t_env));
  node3->key = ft_strdup("dd");
  node3->value = NULL;
  node3->next = NULL;
  node2->next = node3;

  return head;
}

// Print the linked list (for testing purposes)
void print_linked_list(t_env *head) {
  while (head) {
    printf("Key: %s\n", head->key);
    head = head->next;
  }
}

// print the env double
void print_env_list(t_env *env_list) {
  t_env *current = env_list;

  // Traverse the list and print each node's key and value
  while (current != NULL) {
    printf("%s=%s\n", current->key, current->value);
    current = current->next; // Move to the next node
  }
}

int env_size(t_env *lst) {
  int size;

  size = 0;
  while (lst) {
    size++;
    lst = lst->next;
  }
  return (size);
}
// function to transfer list non sorted to a double char sorted
t_env *find_smallest(t_env *head) {
  if (!head)
    return NULL;
  t_env *smallest = head;
  t_env *current = head;
  while (current) {
    if (strcmp(current->key, smallest->key) < 0) {
      smallest = current;
    }
    current = current->next;
  }
  return smallest;
}
void print_export(t_env *env_list) {
  if (!env_list)
    return;
  int i = 0;
  t_env *temp = env_list; // Assign temp to the head, without modifying env_list
  int list_size = env_size(temp);
  char **sorted = (char **)malloc((sizeof(char *) * list_size) + 1);
  t_env *smallest = NULL;
  while (temp) {
    smallest = find_smallest(temp);
    sorted[i] =
        malloc(ft_strlen(smallest->key) + ft_strlen(smallest->value) + 2);
    if (!sorted[i])
      return; // Handle allocation failure
    sprintf(sorted[i], "%s=%s", smallest->key, smallest->value);
    i++;
    temp = temp->next;
  }
  sorted[i] = NULL;
  i = 0;
  while (sorted[i]) {
    printf("declare -x ");
    printf("%s\n", sorted[i]);
    i++;
  }
}
int main(int ac, char **av, char **env) {

  t_env *env_list;
  env_list = NULL;
  env_list = get_env_list(env);
  print_env_list(env_list);

  t_env *head = create_linked_list();
  printf("Before deletion:\n");
  print_linked_list(head);

  // Delete the node with the key "cc"
  delete_node(&head, "cc");

  printf("\nAfter deletion of 'cc':\n");
  print_linked_list(head);

  // Clean up memory
  while (head) {
    t_env *temp = head;
    head = head->next;
    free(temp->key);
    free(temp);
  }

  return 0;
}
