#include "../../includes/minishell.h"
static int filter_args(char *arg)
{
	int i;
	i = 0;
    if (arg[i] == '+' || arg[i] == '-')
    {
        i++;
    }
   
	while (arg[i])
	{
	    if (ft_isdigit(arg[i]) == 0)
		    return 1;
        i++;
	}
    return 0;
}
static int chek_args_number(char **args)
{
    int count;

    count = 0;
    while (args[count])
        count++;
    return count;
}
static void filter_exit(t_container *content, char **args)
{
    if (filter_args(args[0]) == 1)
        {
            ft_putstr_fd("exit\n", 2);
            ft_error_exec_two("bash: exit: ", args[0], ": numeric argument required", 2);
            clean_fds(content->data);
            clear_bin(&content->g_collector);
            clear_bin(&content->g_env_collector);
            write(1, "exit\n", 5);
            exit(255); 
        }
        if (chek_args_number(args + 1) > 0)
        {
            ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
            content->status = 1;
            return;
        }
}
static void clean_exit(t_container *content, int exit_code)
{
    clean_fds(content->data);
    clear_bin(&content->g_collector);
    clear_bin(&content->g_env_collector);
    write(1, "exit\n", 5);
    exit(exit_code);

}

 void handle_exit(t_data *current, t_container *content)
{
    char **args;
    ssize_t number;
    int exit_code;

    args = current->cmds + 1;
    exit_code = 0;
    if (args[0])
    {
        filter_exit(content, args);
        number = ft_atoi(args[0], current, content);
        exit_code = number % 256;
        if (exit_code < 0)
            exit_code += 256; // Normalize negative numbers
        clean_exit(content, exit_code);
    }
    else
    {
        clean_fds(current);
        clear_bin(&content->g_collector);
        clear_bin(&content->g_env_collector);
         write(1, "exit\n", 5);
        exit(0);
    }
}
