/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:51:37 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/15 23:28:27 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_old_pwd(t_env **env_list)
{
	t_env	*current;

	current = NULL;
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
			current->value = NULL;
		current = current->next;
	}
}
static void	update_old_pwd(t_container *content)
{
	t_env	*old_pwd;

	old_pwd = check_if_there("OLDPWD", &content->env_list);
	if (old_pwd)
	{
		if (content->save_path != NULL)
			old_pwd->value = ft_strdup(content->save_path,
					&content->g_env_collector);
		else
			old_pwd->value = ft_strdup("", &content->g_env_collector);
	}
	else
		lstadd_back_env(&content->env_list, lstnew_env("OLDPWD",
				content->save_path, &content->g_env_collector, 1));
}

void	update_original_pwd(t_container *content, char *path)
{
	t_env	*pwd;
	t_env	*cpwd;

	update_old_pwd(content);
	pwd = check_if_there("PWD", &content->env_list);
	if (pwd && path)
		pwd->value = ft_strdup(path, &content->g_env_collector);
	else if (path)
		lstadd_back_env(&content->env_list, lstnew_env("PWD", path,
				&content->g_env_collector, 1));
	cpwd = check_if_there("CPWD", &content->env_list);
	if (check_if_there("PWD", &content->env_list) != NULL
		&& check_if_there("PWD", &content->env_list)->value != NULL)
	{
		if (cpwd)
			cpwd->value = check_if_there("PWD", &content->env_list)->value;
	}
}
