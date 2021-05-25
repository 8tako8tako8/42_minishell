#include "minishell.h"

int	exec_builtin(char **argv, t_mini *mini, int is_parent_proc)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(mini, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(mini));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, mini));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, &mini->env));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(argv, mini->env));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv, mini, is_parent_proc));
	return (0);
}

int	is_builtin(const char *arg)
{
	int			i;
	const char	*builtin_str[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};

	if (arg == NULL)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(arg, builtin_str[i]))
			return (1);
		i++;
	}
	return (0);
}
