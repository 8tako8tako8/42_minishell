#include "minishell.h"

int	put_error_builtin(char *cmd, char *err_str, char *target)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	if (target)
	{
		ft_putstr_fd("`", STDERR);
		ft_putstr_fd(target, STDERR);
		ft_putstr_fd("'", STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(err_str, STDERR);
	ft_putchar_fd('\n', STDERR);
	return (0);
}
