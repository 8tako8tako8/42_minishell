#include "minishell.h"

static	int	open_file(int type, char *file)
{
	if (type == INPUT)
		return (open(file, O_RDONLY));
	else if (type == TRUNC)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (0);
}

static int	open_redirect_file(t_redirect *redir)
{
	if (check_redirect_filename(redir) == INVALID_REDIRECT)
		return (INVALID_REDIRECT);
	redir->fd_open = open_file(redir->type, redir->file);
	if (redir->fd_open < 0)
	{
		if (redir->fd_io == -1)
			put_error_open(FD_OUT_OF_RANGE);
		else
			put_error_open(redir->file);
		return (INVALID_REDIRECT);
	}
	if (check_redirect_fd(redir) == INVALID_REDIRECT)
		return (INVALID_REDIRECT);
	return (VALID_REDIRECT);
}

int	open_redirect_lst(t_redirect *redirect)
{
	t_redirect	*redir;

	if (redirect == NULL)
		return (REDIRECT_SUCCESS);
	redir = redirect;
	while (redir)
	{
		if (open_redirect_file(redir) == INVALID_REDIRECT)
			return (REDIRECT_FAIL);
		redir = redir->next;
	}
	return (REDIRECT_SUCCESS);
}
