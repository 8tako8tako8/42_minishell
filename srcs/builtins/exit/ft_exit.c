#include "minishell.h"

static int	too_many_arguments(t_mini *mini, int is_parent_proc)
{
	mini->exit_error = 1;
	put_error_exit("exit", TOO_MANY_ARGUMENTS, NULL, is_parent_proc);
	return (STATUS_FAIL);
}

static void	numeric_argument_required(char *arg, int is_parent_proc)
{
	put_error_exit("exit", NUMERIC_ARGUMENT_REQUIRED, arg, is_parent_proc);
	exit(255);
}

static int	check_error_exit(char **argv, t_mini *mini,
	int is_parent_proc)
{
	int		argc;

	argc = ft_doublesize((void **)argv) - 1;
	if (argc > 3)
		return (too_many_arguments(mini, is_parent_proc));
	if (argc == 3)
	{
		if (ft_strcmp(argv[1], "--") == 0 && is_number(argv[2]))
			return (too_many_arguments(mini, is_parent_proc));
		else if (ft_strcmp(argv[1], "--") == 0)
			numeric_argument_required(argv[2], is_parent_proc);
	}
	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "--") == 0 && !is_number(argv[2]))
			numeric_argument_required(argv[2], is_parent_proc);
		else if (ft_strcmp(argv[1], "--") != 0 && !is_number(argv[1]))
			numeric_argument_required(argv[2], is_parent_proc);
		else if (ft_strcmp(argv[1], "--") != 0)
			return (too_many_arguments(mini, is_parent_proc));
	}
	if (argc == 1 && ft_strcmp(argv[1], "--") != 0 && !is_number(argv[1]))
		numeric_argument_required(argv[1], is_parent_proc);
	return (0);
}

static void	success_exit(t_mini *mini, int is_parent_proc)
{
	if (is_parent_proc)
		ft_putendl_fd("exit", STDERR);
	exit(mini->ret);
}

int	ft_exit(char **argv, t_mini *mini, int is_parent_proc)
{
	int		i;

	if (argv[1] == NULL || (ft_strcmp(argv[1], "--") == 0 && argv[2] == NULL))
		success_exit(mini, is_parent_proc);
	if (check_error_exit(argv, mini, is_parent_proc) == STATUS_FAIL)
		return (STATUS_FAIL);
	i = 1;
	if (!is_number(argv[i]))
		i++;
	mini->ret = calc_exit_status(ft_atoi_in_exit(argv[i], is_parent_proc));
	success_exit(mini, is_parent_proc);
	return (0);
}
