/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:15:28 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/26 17:57:08 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_split_equal_to(const char *s, t_container *content)
{
	char	**str;
	size_t	len;
	size_t	j;

	if (s == NULL)
		return (NULL);
	str = gc(sizeof(char *) * 3, &content->g_collector, content);
	len = ft_strlen(s);
	j = 0;
	while (s[j] != '=' && s[j] != '\0')
		j++;
	if (s[j] == '=')
	{
		str[0] = ft_substr(s, 0, j, content);
		str[1] = ft_substr(s, j + 1, len - j, content);
	}
	else
	{
		str[0] = ft_strdup(s, &content->g_collector, content);
		str[1] = NULL;
	}
	str[2] = NULL;
	return (str);
}

static void	get_pwd_part2(t_env **env_list, t_container *content, char *pwd)
{
	if (check_if_there("PWD", env_list) != NULL)
		check_if_there("PWD", env_list)->value = ft_strdup(pwd,
			&content->g_env_collector, content);
	else
		lstadd_back_env(env_list, lstnew_env("PWD", pwd, content, 0));
	get_pwd_part3(content, env_list);
}

static void	get_pwd(t_env **env_list, t_container *content)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("shell-init: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		get_pwd_part2(env_list, content, pwd);
		free(pwd);
	}
}

static void	check_flags(t_env *returned_env, t_container *content, int flag)
{
	(void)flag;
	if (check_if_there("OLDPWD", &returned_env) == NULL)
		lstadd_back_env(&returned_env, lstnew_env("OLDPWD", NULL, content, 0));
	else
		clean_old_pwd(&returned_env);
}

t_env	*get_env_list(char **env, t_container *content)
{
	int		i;
	t_env	*returned_env;
	char	**temp;
	int		flag;

	i = 0;
	returned_env = NULL;
	flag = 0;
	if (!env || !env[0])
		env = get_backup_env(content);
	while (env[i])
	{
		temp = ft_split_equal_to(env[i], content);
		lstadd_back_env(&returned_env, lstnew_env(temp[0], temp[1], content,
				0));
		i++;
	}
	check_flags(returned_env, content, flag);
	get_pwd(&returned_env, content);
	return (returned_env);
}
