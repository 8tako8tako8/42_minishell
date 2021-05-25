#include "minishell.h"

void	init_env(t_mini *mini)
{
	mini->env = create_envlst();
	set_pwd(mini);
	increment_shlvl(mini);
	delete_env(&mini->env, "OLDPWD");
	add_envlst_back(&mini->env, create_new_envlst_key_value("OLDPWD", NULL));
}
