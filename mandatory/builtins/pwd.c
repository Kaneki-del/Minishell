#include "../../includes/minishell.h"

void handle_pwd(t_env **env_list)
{
    t_env *temp;
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) == NULL) 
    {
        temp = check_if_there("PWD", env_list);
        if (temp)
            printf("%s\n", temp->value);
    
    } else {
        printf("%s\n", buffer);
    }
}