/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:26 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/23 00:19:18 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_cmd(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit\n", 5);
}

void	ctrl_c_herdoc(int sig)
{
	close(0);
	g_sig = sig;
}

void	ctrl_c(int sig)
{
	printf("\n");
	g_sig = sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
