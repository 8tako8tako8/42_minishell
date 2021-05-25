#include "minishell.h"

int	put_error_open(char *file)
{
	int	err_num;

	err_num = errno;
	ft_putstr_fd("minishell: ", STDERR);
	if (file)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(strerror(err_num), STDERR);
	ft_putchar_fd('\n', STDERR);
	return (0);
}

int	put_error_redirect(char *file, int fd, char *str)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (file)
		ft_putstr_fd(file, STDERR);
	else if (fd == -1)
		ft_putstr_fd(FD_OUT_OF_RANGE, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putchar_fd('\n', STDERR);
	return (0);
}
