#include "../../includes/minishell.h"
#include <string.h>

// updte the old pwd if the cd run succesfully
void update_old_pwd(t_container *content)
{
	t_env	*old_pwd;
	char *pwd;

	old_pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		old_pwd = check_if_there("OLDPWD", &content->env_list);
		if (old_pwd != NULL)
			old_pwd->value = ft_strdup(pwd, &content->g_env_collector);
		else
			lstadd_back_env(&content->env_list, lstnew_env("OLDPWD", pwd, &content->g_env_collector, 1));
	}
}
// function that creat or update the hiden old pwd
void	update_original_pwd(t_container *content, char *path)
{
	t_env *old_pwd;
	t_env *pwd;
	old_pwd = check_if_there("OLDPWD", &content->env_list);
	if (old_pwd)
		old_pwd->value = ft_strdup(content->save_path, &content->g_env_collector);
	else
		lstadd_back_env(&content->env_list, lstnew_env("OLDPWD", content->save_path, &content->g_env_collector, 1));
	pwd = check_if_there("PWD", &content->env_list);
	if (pwd)
		pwd->value = ft_strdup(path, &content->g_env_collector);
	else 
		lstadd_back_env(&content->env_list, lstnew_env("PWD", path, &content->g_env_collector, 1));
}

// create a stored pwd

// void	updte_old_pwd(t_env **env_list, t_gc *env_gc)
// {
// 	char	buffer[PATH_MAX];
// 	t_env	*temp;

// 	// get the current path
// 	if (getcwd(buffer, sizeof(buffer)) == NULL)
// 	{
// 		perror("getcwd failed");
// 		return ;
// 	}
// 	temp = NULL;
// 	temp = check_if_there(".OLDPWD", env_list);
// 	if (temp != NULL)
// 		temp->value = ft_strdup(buffer, &env_gc);
// 	else
// 		lstadd_back_env(env_list, lstnew_env(".OLDPWD", ft_strdup(buffer, &env_gc), &env_gc, 1));
// }
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
	char *current_pwd = getcwd(NULL, 0);

	if (current_pwd == NULL)
	{
		current_pwd = check_if_there("PWD", &content->env_list)->value;
		if (!ft_strcmp(new_path, ".."))
			current_pwd = join_chdir(current_pwd, "/..", content);
		if (!ft_strcmp(new_path, "."))
			current_pwd = join_chdir(current_pwd, "/.", content);
	}
	update_original_pwd(content, current_pwd);
}
int	handle_cd(char **new_path, t_container *content)
{
	t_env	*temp;
	char *tmp;
	char *old_pwd;
	
	old_pwd = getcwd(NULL, 0);
	tmp = check_if_there("PWD", &content->env_list)->value;
	if (tmp != NULL)
		content->save_path = tmp;
	else
		content->save_path = old_pwd;
	if (new_path &&new_path[0])
	{
		if (chdir(new_path[0]) == -1)
		{
			perror(new_path[0]);
			return (1);
		}
		else
			update_pwd(content, new_path[0]);
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
	// update_old_pwd(&content->env_list);
	return (0);
}
