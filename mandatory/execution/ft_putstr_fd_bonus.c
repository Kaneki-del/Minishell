/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:20 by sait-nac          #+#    #+#             */
/*   Updated: 2025/02/21 19:26:02 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_putstr_fd(char *s, int fd) 
{
  size_t i;

  if (fd < 0)
    return;
  i = 0;
  if (!s)
    return;
  while (s[i]) {
    write(fd, &s[i], 1);
    i++;
  }
}
