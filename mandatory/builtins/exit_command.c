#include "../../includes/minishell.h"
int filter_args(char *arg)
{
	int i;
	i = 0;
	while (arg[i])
	{
	if (ft_isdigit(arg[i]) == 0)
		return 1;
        i++;
	}
    return 0;
}
int chek_args_number(char **args)
{
    int count;

    count = 0;
    while (args[count])
        count++;
    return count;
}

void handle_exit(char **args)
{
   
    ssize_t number;
    int exit_code;

    exit_code = 0;
    if (args[0])
    {
        if (filter_args(args[0]) == 1)
        {
            printf("exit\nbash: exit: +: numeric argument required\n");
            exit(255); 
        }
        if (chek_args_number(args + 1) > 0){
            printf("exit\nbash: exit: too many arguments\n");
            //TO_DO: reprompt the minishell
        }
        // give the prompt again
        number = ft_atoi(args[0]);    
        exit_code = number % 256;
        if (exit_code < 0)
            exit_code += 256; // Normalize negative numbers
        exit(exit_code);
    }
    else
        exit(0);
}
