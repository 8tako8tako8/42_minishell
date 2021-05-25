#include "minishell.h"

static void	free_env(t_env *env)
{
	free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	delete_env(t_env **env, char *dstkey)
{
	t_env	*curr_env;
	t_env	*prev_env;

	curr_env = *env;
	prev_env = NULL;
	while (curr_env != NULL)
	{
		if (!ft_strcmp(curr_env->key, dstkey))
		{
			if (prev_env == NULL)
				*env = curr_env->next;
			else
				prev_env->next = curr_env->next;
			free_env(curr_env);
			return ;
		}
		prev_env = curr_env;
		curr_env = curr_env->next;
	}
}
