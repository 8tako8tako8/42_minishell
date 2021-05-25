#include "minishell.h"

void	free_envlst(t_env *env)
{
	t_env	*curr_env;
	t_env	*tmp;

	curr_env = env;
	while (curr_env != NULL)
	{
		free(curr_env->key);
		curr_env->key = NULL;
		if (curr_env->value)
		{
			free(curr_env->value);
			curr_env->value = NULL;
		}
		tmp = curr_env->next;
		free(curr_env);
		curr_env = NULL;
		curr_env = tmp;
	}
}
