#include "../../includes/minishell.h"


int handle_cd(char **new_path, t_env **env_list, t_gc **gc)
{
    // t_env *temp = NULL;
    if (new_path[0])
    {
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
    return 0;
    
}