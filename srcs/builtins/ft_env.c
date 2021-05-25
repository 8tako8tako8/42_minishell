#include "minishell.h"

int	ft_env(char **argv, t_env *env)
{
	if (argv[1])
	{
		put_error_builtin("env", ARGUMENTS_ARE_NOT_SUPPORTED, NULL);
		return (STATUS_FAIL);
	}
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->key, STDOUT);
			ft_putstr_fd("=", STDOUT);
			ft_putendl_fd(env->value, STDOUT);
		}
		env = env->next;
	}
	return (STATUS_SUCCESS);
}
