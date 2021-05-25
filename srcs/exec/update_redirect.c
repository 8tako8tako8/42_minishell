#include "minishell.h"

static void	dup_standard_streams(int fd_io, t_mini *mini)
{
	if (fd_io == STDIN && mini->tmp_in < 0)
		mini->tmp_in = dup(STDIN);
	if (fd_io == STDOUT && mini->tmp_out < 0)
		mini->tmp_out = dup(STDOUT);
	if (fd_io == STDERR && mini->tmp_errout < 0)
		mini->tmp_errout = dup(STDERR);
}

static int	is_standard_streams(int fd)
{
	return (fd == STDIN || fd == STDOUT || fd == STDERR);
}

int	update_fd_io_by_redirect(int is_parent_proc, t_redirect *redirect,
	t_mini *mini)
{
	t_redirect	*redir;

	if (redirect == NULL)
		return (REDIRECT_SUCCESS);
	redir = redirect;
	while (redir)
	{
		if (is_parent_proc && is_standard_streams(redir->fd_io))
			dup_standard_streams(redir->fd_io, mini);
		if (dup2(redir->fd_open, redir->fd_io) < 0)
		{
			put_error_fd(redir->fd_io);
			return (REDIRECT_FAIL);
		}
		mini->saved_fd[redir->fd_io] = USED_FD;
		redir = redir->next;
	}
	return (REDIRECT_SUCCESS);
}
