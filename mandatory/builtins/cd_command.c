#include "../../includes/minishell.h"
#include <string.h>

// updte the old pwd if the cd run succesfully
void	update_old_pwd(t_env **env_list)
{
	t_env	*old_pwd;

	old_pwd = NULL;
	old_pwd = check_if_there("OLDPWD", env_list);
	if (old_pwd != NULL)
		old_pwd->value = check_if_there(".OLDPWD", env_list)->value;
}
// function that creat or update the hiden old pwd
void	update_original_pwd(t_container *content, char *path)
{
	t_env	*old;
	old = check_if_there("PWD", &content->env_list);
	if (old != NULL)
		old->value = ft_strdup(path, &content->g_env_collector);
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
		temp->value = ft_strdup(buffer, &env_gc);
	else
		lstadd_back_env(env_list, lstnew_env(".OLDPWD", ft_strdup(buffer, &env_gc), &env_gc));
}
char	*join_chdir(char *currpwd, char *path, t_container *content)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access ", 2);
	ft_putstr_fd("parent directories: No such file or directory\n", 2);
	currpwd = ft_strjoin(currpwd, path, &content->g_collector);
	chdir(currpwd);
	return (currpwd);
}
void update_pwd(t_container *content, char *new_path)
{
	char	*currpwd;
	t_env *tmp;
	currpwd = getcwd(NULL, 0);

	if (currpwd == NULL)
	{
		tmp = check_if_there("PWD", &content->env_list);
		if (tmp)
			currpwd = tmp->value;
		if (!ft_strcmp(new_path, ".."))
			currpwd = join_chdir(currpwd, "/..", content);
		if (!ft_strcmp(new_path, "."))
			currpwd = join_chdir(currpwd, "/.", content);
	
	}
	update_original_pwd(content, currpwd);
}
int	handle_cd(char **new_path, t_container *content)
{
	t_env	*temp;

	updte_old_pwd_hiden(&content->env_list, content->g_env_collector);
	temp = NULL;
	if (new_path &&new_path[0])
	{
		if (chdir(new_path[0]) == -1)
		{
			perror(new_path[0]);
			return (1);
		}
		else
			update_pwd(content, new_path[0]);
	
		// if (chdir(new_path[0]) == -1)
		// 	return (ft_error_exec_two("bash: cd: ", new_path[0], ": No such file or directory", 2), 1);
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
	// update_original_pwd(&content->env_list, content->g_env_collector);
	update_old_pwd(&content->env_list);
	return (0);
}
