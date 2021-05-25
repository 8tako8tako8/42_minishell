#include "minishell.h"

int	put_error_cd(char *dirname)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	ft_putstr_fd(dirname, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	return (0);
}

int	put_error_get_working_directory(char *caller)
{
	ft_putstr_fd(caller, STDERR);
	ft_putstr_fd(": error retrieving current directory", STDERR);
	ft_putstr_fd(": getcwd: cannot access parent directories: ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	return (0);
}
