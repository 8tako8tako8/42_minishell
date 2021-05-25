#include "minishell.h"

int	put_error_exit(char *cmd, char *err_str, char *arg, int is_parent_proc)
{
	if (is_parent_proc)
		ft_putendl_fd("exit", STDERR);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(err_str, STDERR);
	ft_putchar_fd('\n', STDERR);
	return (0);
}
