#include "minishell.h"

int	set_redirect(int is_parent_proc, t_redirect *redirect, t_mini *mini)
{
	if (open_redirect_lst(redirect) == REDIRECT_FAIL)
		return (REDIRECT_FAIL);
	if (update_fd_io_by_redirect(is_parent_proc, redirect, mini)
		== REDIRECT_FAIL)
		return (REDIRECT_FAIL);
	return (REDIRECT_SUCCESS);
}
