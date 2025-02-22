#include "../../includes/minishell.h"

void handle_pwd(void)
{
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) == NULL) 
    {
        perror("getcwd failed");
    } else {
        printf("%s\n", buffer);
    }
}