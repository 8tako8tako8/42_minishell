#include "minishell.h"

t_env	*create_new_envlst_key_value(
										char const *key, const char *value)
{
	t_env	*new_env;

	new_env = (t_env *)wrap_malloc(sizeof(t_env));
	new_env->key = strdup_safely((char *)key);
	if (value)
		new_env->value = strdup_safely((char *)value);
	else
		new_env->value = NULL;
	new_env->next = NULL;
	return (new_env);
}

void	bind_env(
		t_mini *mini, const char *key, const char *value, int plus_flag)
{
	t_env	*curr_env;
	t_env	*new_env;

	curr_env = mini->env;
	while (curr_env)
	{
		if (ft_strcmp(curr_env->key, key) == 0)
		{
			update_env_value(plus_flag, curr_env, (char *)value);
			return ;
		}
		curr_env = curr_env->next;
	}
	new_env = create_new_envlst_key_value(key, value);
	add_envlst_back(&mini->env, new_env);
}
