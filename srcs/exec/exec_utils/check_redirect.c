#include "minishell.h"

static int	is_invalid_filename(char *file)
{
	return (file[0] == -1);
}

int	check_redirect_filename(t_redirect *redir)
{
	if (is_invalid_filename(redir->file))
	{
		put_error_redirect(
			redir->before_expand, redir->fd_io, AMBIGUOUS_REDIRECT);
		return (INVALID_REDIRECT);
	}
	else if (ft_strlen(redir->file) == 0)
	{
		put_error_redirect(NULL, redir->fd_io, NO_SUCH_FILE);
		return (INVALID_REDIRECT);
	}
	return (VALID_REDIRECT);
}

int	is_invalid_fd(int fd)
{
	return (fd == -1 || fd > 255);
}

int	check_redirect_fd(t_redirect *redir)
{
	if (is_invalid_fd(redir->fd_io))
	{
		put_error_fd(redir->fd_io);
		return (INVALID_REDIRECT);
	}
	return (VALID_REDIRECT);
}
