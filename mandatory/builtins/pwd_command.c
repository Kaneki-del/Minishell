/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:02:41 by sait-nac          #+#    #+#             */
/*   Updated: 2025/03/21 16:05:44 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_pwd_error(t_container *content)
{
	content->status = 1;
	ft_putstr_fd("pwd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access ", 2);
	ft_putstr_fd("parent directories: No such file or directory\n", 2);
}

void	handle_pwd(t_container *content, t_data *current)
{
	t_env	*temp;
	char	*pwd;
	t_env	**env_list;
	int		saved_stdout;

	env_list = &content->env_list;
	pwd = getcwd(NULL, 0);
	saved_stdout = rideraction_builtins(current, content);
	if (pwd == NULL)
	{
		temp = check_if_there("CPWD", env_list);
		if (temp)
			printf("%s\n", temp->value);
		else
			print_pwd_error(content);
	}
	else
		(printf("%s\n", pwd), free(pwd));
	if (saved_stdout != -1)
	{
		if (dup2(saved_stdout, 1) == -1)
			(perror("error in dup2"), clean_exit2(content, 1));
		close(saved_stdout);
	}
}
