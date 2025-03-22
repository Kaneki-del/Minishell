#include "../../includes/minishell.h"

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
    if (i > 0 && ft_strncmp(cmds[i - 1], "<<", 3) != 0)
    {
      cmds[i] = remove_quotes(cmds[i], g_collector);
      if (!cmds[i])
        return (NULL);
    }
    else if (ft_strncmp(cmds[i], "''", 3) == 0 || ft_strncmp(cmds[i], "\"\"", 3) == 0)
      cmds[i] = remove_quotes(cmds[i], g_collector);
    i++;
  }
  return (cmds);
}

int check_is_in_qoutes(char *str)
{
  if (str && (str[0] == '"' || str[0] == '\'') \
  && (str[ft_strlen(str) - 1] == '"' || str[ft_strlen(str) - 1] == '\''))
    return (1);
  return (0);
}

char *add_qoutations(char *command, t_gc **g_collector)
{
  int i;
  int j;
  char *res;

  i = 0;
  j = 1;
  if (check_is_in_qoutes(command))
      return (command);
  res = gc(ft_strlen(command) + 3, g_collector);
  res[0] = '"';
  while (command[i])
  {
    res[j] = command[i];
    i++;
    j++;
  }
  res[j] = '"';
  res[j + 1] = '\0';
  return (res);
}
