#include "../../includes/minishell.h"

int handle_cd(char **new_path, t_env **env_list, t_gc **gc)
{
    // updte_old_pwd_hiden(env_list);
    //t_env *temp = NULL;
    if (new_path[0])
    {
        
        // update the old pwd to the get_cd
        // and if there .OLDPWD UPDATE it else add it back 
        if (chdir(new_path[0]) == -1) {
            perror("chdir failed");
            return 1;
        }
    }
    else 
    {
        // temp = check_if_there("HOME", env_list); 
        if (chdir(check_if_there("HOME", env_list)->value) == -1) {
            return (ft_error("bash: cd: HOME not set", NULL, 2, gc), 1);
        }
    }
    // update_original_pwd(env_list);
    // update_old_pwd(env_list);
    return 0;
}
