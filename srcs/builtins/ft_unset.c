#include "minishell.h"

int	ft_unset(char **argv, t_env **env)
{
	int		i;
	int		ret_status;

	ret_status = 0;
	i = 0;
	while (argv[++i])
	{
		if (!is_underscore_or_alpha(argv[i][0]) || is_invalid_key(argv[i]))
		{
			put_error_builtin("unset", NOT_A_VALID_IDENTIFIER, argv[i]);
			ret_status = 1;
			continue ;
		}
		delete_env(env, argv[i]);
	}
	return (ret_status);
}
