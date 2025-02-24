#include "../../includes/minishell.h"
#include <string.h>

// updte the old pwd if the cd run succesfully
void	update_old_pwd(t_env **env_list)
{
	t_env	*old_pwd;

	old_pwd = NULL;
	old_pwd = check_if_there("OLDPWD", env_list);
	if (old_pwd != NULL)
	{
		// free(old_pwd->value);
		old_pwd->value = check_if_there(".OLDPWD", env_list)->value;
	}
}
// function that creat or update the hiden old pwd
void	update_original_pwd(t_env **env_list)
{
	t_env	*old;
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("getcwd failed");
		return ;
	}
	old = check_if_there("PWD", env_list);
	if (old != NULL)
	{
		old->value = strdup(buffer);
	}
}

// create a stored pwd

void	updte_old_pwd_hiden(t_container *content)
{
	char	buffer[PATH_MAX];
	t_env	*temp;

	// get the current path
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("getcwd failed");
		return ;
	}
	temp = NULL;
	temp = check_if_there(".OLDPWD", &content->env_list);
	if (temp != NULL)
	{
		// free(temp->value);
		temp->value = strdup(buffer);
	}
	else 
		lstadd_back_env(&content->env_list, lstnew_env(".OLDPWD", strdup(buffer), &content->g_collector));
}

int	handle_cd(char **new_path, t_container *content)
{
	t_env	*temp;

	updte_old_pwd_hiden(content);
	temp = NULL;
	if (new_path && new_path[0])
	{
		
		if (chdir(new_path[0]) == -1)
		{
			perror("chdir failed");
			return (1);
		}
	}
	else
	{
		temp = check_if_there("HOME", &content->env_list);
		if (chdir(check_if_there("HOME", &content->env_list)->value) == -1)
			return (ft_error("bash: cd: HOME not set", NULL, 2, &content->g_collector), 1);
	}
	update_original_pwd(&content->env_list);
	update_old_pwd(&content->env_list);
	return (0);
}
