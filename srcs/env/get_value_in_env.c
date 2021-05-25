#include "minishell.h"

char	*get_value_in_env(t_env *env, char *dstkey)
{
	if (!env || !dstkey)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, dstkey) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
