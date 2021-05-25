#include "minishell.h"

static void	restore_standard_streams(t_mini *mini)
{
	if (mini->tmp_in >= 0)
	{
		if (dup2(mini->tmp_in, STDIN) < 0)
			put_error_and_exit();
		mini->tmp_in = -1;
	}
	if (mini->tmp_out >= 0)
	{
		if (dup2(mini->tmp_out, STDOUT) < 0)
			put_error_and_exit();
		mini->tmp_out = -1;
	}
	if (mini->tmp_errout >= 0)
	{
		if (dup2(mini->tmp_errout, STDERR) < 0)
			put_error_and_exit();
		mini->tmp_errout = -1;
	}
}

static void	close_redirect_fd(t_redirect *redirect, t_mini *mini)
{
	t_redirect	*redir;

	if (redirect == NULL)
		return ;
	redir = redirect;
	while (redir)
	{
		if (redir->fd_open >= 0)
		{
			if (close(redir->fd_open) < 0)
				put_error_and_exit();
			mini->saved_fd[redir->fd_open] = UNUSED_FD;
		}
		if (!is_invalid_fd(redir->fd_io) && mini->saved_fd[redir->fd_io]
			== USED_FD)
		{
			if (close(redir->fd_io) < 0)
				put_error_and_exit();
			mini->saved_fd[redir->fd_io] = UNUSED_FD;
		}
		redir = redir->next;
	}
}

static	int	set_redirect_and_exec_builtin(t_command *cmd, t_mini *mini)
{
	if (set_redirect(PARENT_PROC, cmd->redirect, mini) == REDIRECT_FAIL)
		return (STATUS_FAIL);
	return (exec_builtin(cmd->argv, mini, PARENT_PROC));
}

int	exec_builtin_in_parent_proc(t_command *cmd, t_mini *mini)
{
	int			exit_status;

	exit_status = set_redirect_and_exec_builtin(cmd, mini);
	close_redirect_fd(cmd->redirect, mini);
	restore_standard_streams(mini);
	return (exit_status);
}
