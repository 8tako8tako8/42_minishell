#include "minishell.h"

static void	overwrite_value(t_env *curr_env, char *value)
{
	char	*tmp;

	tmp = curr_env->value;
	curr_env->value = strdup_safely(value);
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
}

static void	add_value_to_old_value(t_env *curr_env, char *value)
{
	char	*tmp;

	if (!curr_env->value)
		curr_env->value = strdup_safely(value);
	else
	{
		tmp = curr_env->value;
		curr_env->value = strjoin_safely(curr_env->value, value);
		if (tmp != NULL)
			free(tmp);
	}
}

void	update_env_value(int plus_flag, t_env *curr_env, char *value)
{
	if (value)
	{
		if (plus_flag)
			add_value_to_old_value(curr_env, value);
		else
			overwrite_value(curr_env, value);
	}
}
