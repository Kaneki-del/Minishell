/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:11:45 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/24 23:35:23 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_backup_env(t_container *content)
{
	char	**new_env;

	new_env = (char **)gc(4 * sizeof(char *), &content->g_collector, content);
	new_env[0] = ft_strdup("PWD=/Users/sait-nac", &content->g_collector,
			content);
	new_env[1] = ft_strdup("SHLVL=1", &content->g_collector, content);
	new_env[2] = ft_strdup("_=/usr/bin/env", &content->g_collector, content);
	new_env[3] = NULL;
	return (new_env);
}
