#include "../../includes/minishell.h"

char *filer_qoutations(char *command_line,  t_gc **g_collector)
{
  int i;
  int j;
  int in_qoute;
  char qoute;
  char *words_between;

  in_qoute = 0;
  j = 0;
  i = 0;
  if (!command_line)
    return (NULL);
  words_between = gc(ft_strlen(command_line) + 1, g_collector);
  if (!words_between)
    return (clear_bin(g_collector), NULL); // shoud handle
  while (command_line[i])
  {
    if ((command_line[i] == '"' || command_line[i] == '\'') && !in_qoute) {
      qoute = command_line[i];
      (in_qoute = 1, i++);
    }
    else if (command_line[i] == qoute && in_qoute)
      (in_qoute = 0, i++);
    else
      words_between[j++] = command_line[i++];
  }
  words_between[j] = '\0';
  return (words_between);
}

char *filter_one_sides(char *command_line,  t_gc **g_collector)
{
  size_t i;
  int j;
  char *words_between;

  j = 0;
  i = 1;
  if (!command_line)
    return (NULL);
  if (!check_is_in_qoutes(command_line))
    return (command_line);
  words_between = gc(ft_strlen(command_line) + 1, g_collector);
  if (!words_between)
    return (NULL); // shoud handle
  while (command_line[i] && i < ft_strlen(command_line) - 1)
  {
    words_between[j++] = command_line[i++];
  }
  words_between[j] = '\0';  
  return (words_between);
}

char **filterd(char **cmds,t_gc **g_collector)
{
  int i;
  

  i = 0;
  if (!cmds)
    return (NULL);
  while (cmds[i] != NULL)
  {
    if (ft_strncmp(cmds[i - i], "<<", 3) != 0)
    {
      cmds[i] = filer_qoutations(cmds[i], g_collector);
      if (!cmds[i])
        return (NULL);
    }
    i++;
  }
  return (cmds);
}

int check_is_in_qoutes(char *str)
{
  if (str && (str[0] == '"' || str[0] == '\'') && (str[ft_strlen(str) - 1] == '"' || str[ft_strlen(str) - 1] == '\''))
    return (1);
  return (0);
}