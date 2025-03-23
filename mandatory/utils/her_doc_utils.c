/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:23:14 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/22 21:41:01 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prioritize_herdoc(t_data *list, char **rideractions, t_container *content)
{
	int	i;

	if (!rideractions || !rideractions[0])
		return (0);
	i = 0;
	while (rideractions[i])
	{
		if (ft_strcmp(rideractions[i], "<<") == 0)
		{
			i++;
			if (list->in_fd != 0)
				close(list->in_fd);
			list->in_fd = her_doc(rideractions[i], content);
			if (list->in_fd == -3)
				return (-3);
		}
		i++;
	}
	return (0);
}
