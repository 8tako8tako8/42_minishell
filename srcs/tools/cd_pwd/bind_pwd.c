#include "minishell.h"

int	bind_pwd(t_mini *mini)
{
	char	*dirname;
	char	*pwd_str;

	if (mini->the_current_working_directory)
		dirname = mini->the_current_working_directory;
	else
		dirname = get_working_directory(mini, "cd");
	pwd_str = get_value_in_env(mini->env, "PWD");
	bind_env(mini, "OLDPWD", pwd_str, 0);
	bind_env(mini, "PWD", dirname, 0);
	if (dirname != mini->the_current_working_directory)
		free(dirname);
	free(pwd_str);
	return (0);
}
