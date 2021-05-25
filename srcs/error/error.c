#include "minishell.h"

int	put_error_fd(int fd)
{
	char	*nbr;

	ft_putstr_fd("minishell: ", STDERR);
	if (fd == -1)
		ft_putstr_fd(FD_OUT_OF_RANGE, STDERR);
	else
	{
		nbr = ft_itoa(fd);
		ft_putstr_fd(nbr, STDERR);
		free(nbr);
	}
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(BAD_FD, STDERR);
	ft_putchar_fd('\n', STDERR);
	return (0);
}

int	put_error(char *err_str, char *target)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(err_str, STDERR);
	if (target)
	{
		ft_putstr_fd(" `", STDERR);
		ft_putstr_fd(target, STDERR);
		ft_putstr_fd("'", STDERR);
	}
	ft_putchar_fd('\n', STDERR);
	return (0);
}

void	put_error_and_exit(void)
{
	int	err_num;

	err_num = errno;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(strerror(err_num), STDERR);
	ft_putchar_fd('\n', STDERR);
	exit(1);
}

int	put_error_binary(char *cmd, char *err_str)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(err_str, STDERR);
	ft_putchar_fd('\n', STDERR);
	return (0);
}
