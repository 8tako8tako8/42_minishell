#include "minishell.h"

int	mark_env(char *s)
{
	size_t	i;
	int		is_marked;

	i = 0;
	is_marked = 0;
	while (s[i])
	{
		if (s[i] == '$' && !is_escaped(s, i)
			&& ft_isquoting(s, i + 1) != SQUOTE)
		{
			s[i] = -'$';
			is_marked = 1;
		}
		i++;
	}
	return (is_marked);
}

int	calc_argc(char **lst)
{
	int	ac;

	ac = 0;
	while (*lst)
	{
		if (is_redir_op(*lst))
			lst++;
		else
			ac++;
		if (*lst)
			lst++;
	}
	return (ac);
}

static char	**expand_env(t_mini *mini, char **argv, char *before)
{
	char	**ret;
	char	**tmp;
	char	**quote_expanded;
	char	*env_expanded;

	env_expanded = expand_environment(mini, before);
	if (!env_expanded)
	{
		ret = (char **)ft_doubledup((void **)argv);
		if (!ret)
			put_error_and_exit();
		return (ret);
	}
	tmp = ft_split_quote_escape(env_expanded, ' ');
	if (!tmp)
		put_error_and_exit();
	quote_expanded = (char **)ft_doublemap((void **)tmp, &expand_quote_escape);
	if (!quote_expanded)
		put_error_and_exit();
	ret = (char **)ft_doublejoin((void **)argv, (void **)quote_expanded);
	ft_free_double((void ***)&quote_expanded);
	ft_free_double((void ***)&tmp);
	ft_free((void **)&env_expanded);
	return (ret);
}

char	**expand_arg(t_mini *mini, char **argv, const char *str)
{
	char	*before;
	char	*quote_expanded;
	char	**ret;

	before = strdup_safely((char *)str);
	if (mark_env(before))
		ret = expand_env(mini, argv, before);
	else
	{
		quote_expanded = expand_quote_escape(before);
		ret = (char **)ft_doubleadd_back((void **)argv, (void *)quote_expanded);
	}
	ft_free((void **)&before);
	ft_free_double((void ***)&argv);
	return (ret);
}

char	**create_argv(t_mini *mini, char **lst, int argc)
{
	char	**argv;

	(void)argc;
	argv = (char **)wrap_malloc(sizeof(char *));
	*argv = NULL;
	while (*lst)
	{
		if (is_redir_op(*lst))
			lst++;
		else
			argv = expand_arg(mini, argv, *lst);
		if (*lst)
			lst++;
	}
	return (argv);
}
