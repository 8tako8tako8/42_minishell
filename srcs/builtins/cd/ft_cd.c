#include "minishell.h"

int	ft_cd(t_mini *mini, char **argv)
{
	char	*dirname;

	if (argv[1] == NULL)
		return (SUCCESS);
	dirname = argv[1];
	if (change_to_directory(mini, dirname))
		return (bind_pwd(mini));
	put_error_cd(dirname);
	return (ERROR);
}
