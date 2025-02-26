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
		// free(old->value);
		old->value = strdup(buffer);
	}
}

// create a stored pwd

void	updte_old_pwd_hiden(t_env **env_list, t_gc *env_gc)
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
	temp = check_if_there(".OLDPWD", env_list);
	if (temp != NULL)
	{
		// free(temp->value);
		temp->value = strdup(buffer);
	}
	else
		lstadd_back_env(env_list, lstnew_env(".OLDPWD", strdup(buffer), &env_gc));
}

int	handle_cd(char **new_path, t_container *content)
{
	t_env	*temp;

	updte_old_pwd_hiden(&content->env_list, content->g_env_collector);
	temp = NULL;
	if (new_path &&new_path[0])
	{
		// update the old pwd to the get_cd
		// and if there .OLDPWD UPDATE it else add it back
			//bash: cd: sngrsd: No such file or directory
		if (chdir(new_path[0]) == -1)
			return (ft_error_exec_two("bash: cd: ", new_path[0], ": No such file or directory", 2), 1);
	}
	else
	{
		temp = check_if_there("HOME", &content->env_list);
		if (temp != NULL){
			if (chdir(temp->value) == -1)
				return (0);
		}
		else 
			return (ft_error_exec_two("bash: cd", ": HOME", " not set",  2), 1);
	}
	update_original_pwd(&content->env_list);
	update_old_pwd(&content->env_list);
	return (0);
}
