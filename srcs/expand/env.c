#include "minishell.h"

static int	is_env_sep(char c)
{
	return (!(ft_isalpha(c) || ft_isdigit(c) || c == '_'));
}

static char	*get_env_value(t_env *env, const char *s, int *i, int *j)
{
	char	*val;
	char	*tmp;

	val = ft_substr(s, *i, *j);
	if (!val)
		put_error_and_exit();
	tmp = val;
	val = get_value_in_env(env, val);
	ft_free((void **)&tmp);
	if (val)
	{
		tmp = val;
		val = escape_str(val);
		ft_free((void **)&tmp);
	}
	return (val);
}

static char	*get_last_exit_status_str(t_mini *mini, int *j)
{
	char	*ret;

	(*j)++;
	ret = ft_itoa(mini->ret);
	if (!ret)
		put_error_and_exit();
	return (ret);
}

static void	expand_environment_sub(
								t_mini *mini, const char *s, char **p, int *i)
{
	char	*tmp;
	char	*val;
	int		j;

	j = 0;
	(*i)++;
	while (!is_env_sep(s[*i + j]))
		j++;
	if (j == 0 && s[*i + j] == '?')
		val = get_last_exit_status_str(mini, &j);
	else if (j)
		val = get_env_value(mini->env, s, i, &j);
	else
		val = strdup_safely("$");
	if (val)
	{
		tmp = *p;
		*p = ft_strjoin(*p, val);
		if (!*p)
			put_error_and_exit();
		ft_free((void **)&tmp);
		ft_free((void **)&val);
	}
	*i += j;
}

char	*expand_environment(t_mini *mini, const char *s)
{
	char	*p;
	char	*tmp;
	int		i;
	int		joined;

	p = strdup_safely("");
	i = 0;
	joined = 0;
	while (s[i])
	{
		if (s[i] == -'$')
			expand_environment_sub(mini, s, &p, &i);
		else
		{
			tmp = p;
			p = charjoin_safely(p, s[i++]);
			ft_free((void **)&tmp);
			joined = 1;
		}
	}
	if (ft_strlen(p) > 0 || joined)
		return (p);
	ft_free((void **)&p);
	return (NULL);
}
