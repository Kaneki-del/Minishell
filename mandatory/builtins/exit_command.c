#include "../../includes/minishell.h"
int filter_args(char *arg)
{
	int i;
	i = 0;
    if (arg[i] == '+' || arg[i] == '-')
        i++;
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

int handle_exit(char **args, t_container *content)
{
   
    ssize_t number;
    int exit_code;

    exit_code = 0;
    if (args[0])
    {
        //bash: exit: +e: numeric argument required
        if (filter_args(args[0]) == 1)
        {
            ft_putstr_fd("exit\n", 2);
            ft_error_exec_two("bash: exit: ", args[0], ": numeric argument required", 2);
            clear_bin(&content->g_collector);
            clear_bin(&content->g_env_collector);
            exit(255); 
        }
        //bash: exit: too many arguments
        if (chek_args_number(args + 1) > 0){
            ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
            return 1;
        }
        // give the prompt again
        number = ft_atoi(args[0]);    
        exit_code = number % 256;
        if (exit_code < 0)
            exit_code += 256; // Normalize negative numbers
        clear_bin(&content->g_collector);
        clear_bin(&content->g_env_collector);
        exit(exit_code);
    }
    else
    {
        clear_bin(&content->g_collector);
        clear_bin(&content->g_env_collector);
        exit(0);
    }
}
