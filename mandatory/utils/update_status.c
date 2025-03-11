#include "../../includes/minishell.h"

void update_status(t_container *content)
{
    if (WIFEXITED(content->status))
		content->status = WEXITSTATUS(content->status);
	else if (WIFSIGNALED(content->status))
		content->status = WTERMSIG(content->status) + 128;
}