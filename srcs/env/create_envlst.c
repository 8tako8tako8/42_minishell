#include "minishell.h"

static void	strdup_key_and_value(const char *str, t_env **new_env,
	char *equal_ptr)
{
	if (equal_ptr == NULL)
	{
		(*new_env)->key = strdup_safely(str);
		(*new_env)->value = NULL;
	}
	else
	{
		(*new_env)->key = substr_safely(str, 0, equal_ptr - str);
		(*new_env)->value = strdup_safely(equal_ptr + 1);
	}
}

t_env	*create_new_envlst(const char *str)
{
	t_env	*new_env;
	char	*equal_ptr;

	new_env = (t_env *)wrap_malloc(sizeof(t_env));
	equal_ptr = ft_strchr(str, '=');
	strdup_key_and_value(str, &new_env, equal_ptr);
	new_env->next = NULL;
	return (new_env);
}

t_env	*create_envlst(void)
{
	t_env			*env;
	t_env			*new_env;
	extern char		**environ;
	int				shlvl_flag;
	int				i;

	shlvl_flag = 0;
	env = NULL;
	i = 0;
	while (environ[i])
	{
		if (shlvl_flag == 0 && is_shlvl(environ[i]))
			shlvl_flag = 1;
		new_env = create_new_envlst(environ[i]);
		add_envlst_back(&env, new_env);
		i++;
	}
	bind_shlvl(&env, &shlvl_flag);
	return (env);
}
