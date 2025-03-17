/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:45:04 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/17 16:10:14 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_chdir(char *currpwd, char *path, t_container *content)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access ", 2);
	ft_putstr_fd("parent directories: No such file or directory\n", 2);
	if (currpwd[ft_strlen(currpwd) - 1] != '/')
		currpwd = ft_strjoin(currpwd, "/", &content->g_collector);
	currpwd = ft_strjoin(currpwd, path, &content->g_collector);
	return (currpwd);
}

static void	update_pwd(t_container *content, char *new_path)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (current_pwd == NULL)
	{
		if (check_if_there("CPWD", &content->env_list) != NULL)
			current_pwd = check_if_there("CPWD", &content->env_list)->value;
		current_pwd = join_chdir(current_pwd, new_path, content);
	}
	{
		update_original_pwd(content, current_pwd);
		free(current_pwd);
	}
}

static void	cd_home(t_container *content)
{
	t_env	*temp;

	temp = check_if_there("HOME", &content->env_list);
	if (temp != NULL && temp->value != NULL)
	{
		if (!temp->value)
			return ;
		else if (chdir(temp->value) == -1)
		{
			if (!ft_strcmp(temp->value, "\0"))
				return ;
			else
			{
				ft_error_exec_two("mshell: cd: ", temp->value,
					": No such file or directory", 2);
				content->status = 1;
			}
		}
	}
	else
	{
		ft_error_exec_two("mshell: cd", ": HOME", " not set", 2);
		content->status = 1;
	}
}

void	handle_cd(char **new_path, t_container *content)
{
	t_env	*tmp;

	tmp = check_if_there("PWD", &content->env_list);
	if (tmp != NULL && tmp->value != NULL)
		content->save_path = tmp->value;
	else
		content->save_path = ft_strdup("", &content->g_collector);
	if (new_path && new_path[0])
	{
		if (content->flag)
			new_path[0] = remove_quotes(new_path[0], &content->g_collector);
		if (chdir(new_path[0]) == -1)
		{
			perror(new_path[0]);
			content->status = 1;
		}
		else
			update_pwd(content, new_path[0]);
	}
	else
		cd_home(content);
}
