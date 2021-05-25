#include "minishell.h"

static void	expand_quote_escape_squote(char *s, char **p, int i)
{
	char	*tmp;

	if (s[i] == '\'')
		;
	else
	{
		tmp = *p;
		*p = ft_charjoin(*p, s[i]);
		if (!p)
			put_error_and_exit();
		free(tmp);
	}
}

static void	expand_quote_escape_dquote(char *s, char **p, int *i)
{
	char	*tmp;

	tmp = *p;
	if (s[*i] == '\"')
		;
	else
	{
		tmp = *p;
		if (s[*i] && s[*i] == '\\' && ft_strchr("\\$\"", s[(*i) + 1]))
			(*i)++;
		*p = ft_charjoin(*p, s[*i]);
		if (!*p)
			put_error_and_exit();
		free(tmp);
	}
}

static void	expand_quote_escape_normal(char *s, char **p, int *i)
{
	char	*tmp;

	if (s[*i] == '\"' || s[*i] == '\'')
		;
	else
	{
		tmp = *p;
		if (s[*i] == '\"' && ft_isquoting(s, *i + 1))
			(*i)++;
		else if (s[*i] == '\\')
			(*i)++;
		*p = ft_charjoin(*p, s[*i]);
		if (!*p)
			put_error_and_exit();
		free(tmp);
	}
}

char	*expand_quote_escape(char *s)
{
	char	*p;
	int		i;

	p = strdup_safely("");
	if (!s)
		return (p);
	i = 0;
	while (s[i])
	{
		if (ft_isquoting(s, i + 1) == SQUOTE)
			expand_quote_escape_squote(s, &p, i);
		else if (ft_isquoting(s, i + 1) == DQUOTE)
			expand_quote_escape_dquote(s, &p, &i);
		else
			expand_quote_escape_normal(s, &p, &i);
		if (s[i])
			i++;
	}
	return (p);
}
