#include "minishell.h"

void	bind_shlvl(t_env **env, int *shlvl_flag)
{
	t_env	*new_env;

	if (!*shlvl_flag)
	{
		new_env = create_new_envlst("SHLVL=0");
		add_envlst_back(env, new_env);
	}
}

int	is_shlvl(char *environ)
{
	return (!ft_strncmp("SHLVL=", environ, 6));
}
