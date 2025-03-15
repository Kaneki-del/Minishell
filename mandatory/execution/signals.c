/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:26 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/15 23:43:03 by sait-nac         ###   ########.fr       */
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
