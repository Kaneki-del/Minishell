/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:59:50 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 21:59:59 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_status(t_container *content)
{
	if (WIFEXITED(content->status))
		content->status = WEXITSTATUS(content->status);
	else if (WIFSIGNALED(content->status))
		content->status = WTERMSIG(content->status) + 128;
}
