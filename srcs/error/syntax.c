#include "minishell.h"

void	put_error_unexpected_token_fd(int nbr)
{
	char	*fd;

	fd = ft_itoa(nbr);
	if (!fd)
		put_error_and_exit();
	put_error(UNEXPECTED_TOKEN, fd);
	ft_free((void **)&fd);
}

int	put_error_unexpected_token(int nbr)
{
	if (nbr >= 0)
		put_error_unexpected_token_fd(nbr);
	else if (nbr == ERR_FD_OVERFLOW)
		put_error(UNEXPECTED_TOKEN, FD_OVERFLOW_STR);
	else if (nbr == ERR_END)
		put_error(UNEXPECTED_TOKEN, END_STR);
	else if (nbr == ERR_ENDS)
		put_error(UNEXPECTED_TOKEN, ENDS_STR);
	else if (nbr == ERR_PIPE)
		put_error(UNEXPECTED_TOKEN, PIPE_STR);
	else if (nbr == ERR_PIPES)
		put_error(UNEXPECTED_TOKEN, PIPES_STR);
	else if (nbr == ERR_NEWLINE)
		put_error(UNEXPECTED_TOKEN, NEWLINE_STR);
	else if (nbr == ERR_INPUT)
		put_error(UNEXPECTED_TOKEN, INPUT_STR);
	else if (nbr == ERR_TRUNC)
		put_error(UNEXPECTED_TOKEN, TRUNC_STR);
	else if (nbr == ERR_INPUTS)
		put_error(UNEXPECTED_TOKEN, INPUTS_STR);
	else if (nbr == ERR_APPEND)
		put_error(UNEXPECTED_TOKEN, APPEND_STR);
	return (0);
}
