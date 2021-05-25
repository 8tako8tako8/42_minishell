#include "minishell.h"

static int	is_same_directory(char *path1, char *path2)
{
	struct stat	st1;
	struct stat	st2;

	if (stat(path1, &st1) != 0)
		return (0);
	if (stat(path2, &st2) != 0)
		return (0);
	return ((st1.st_dev == st2.st_dev) && (st1.st_ino == st2.st_ino));
}

void	set_pwd(t_mini *mini)
{
	char	*pwd_str;
	char	*home_str;

	home_str = get_value_in_env(mini->env, "HOME");
	pwd_str = get_value_in_env(mini->env, "PWD");
	if (pwd_str && is_same_directory(pwd_str, "."))
		set_working_directory(mini, pwd_str);
	else if (home_str && is_same_directory(home_str, "."))
	{
		set_working_directory(mini, home_str);
		bind_env(mini, "PWD", home_str, 0);
	}
	else
	{
		pwd_str = get_working_directory(mini, "shell-init");
		if (pwd_str)
			bind_env(mini, "PWD", pwd_str, 0);
	}
	ft_free((void **)&home_str);
	ft_free((void **)&pwd_str);
}
