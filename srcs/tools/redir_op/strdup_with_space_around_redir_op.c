#include "minishell.h"

static int	is_redir_with_fd(const char *s, int i)
{
	int	n;

	n = i;
	while (n >= 0)
	{
		if (ft_isdigit(s[n]))
			;
		else if (s[n] == ' ')
			return (i - n);
		else
			return (0);
		n--;
	}	
	return (i - n);
}

static void	add_space_around_append(const char *s, char *new, int *i, int *j)
{
	new[(*j)--] = ' ';
	new[(*j)--] = s[(*i)--];
	new[(*j)--] = s[(*i)--];
	if (is_redir_with_fd(s, *i))
	{
		while (*i >= 0 && ft_isdigit(s[*i]))
			new[(*j)--] = s[(*i)--];
	}
	if (*j >= 0)
		new[(*j)--] = ' ';
}

static void	add_space_around_trunc_or_input(
									const char *s, char *new, int *i, int *j)
{
	new[(*j)--] = ' ';
	new[(*j)--] = s[(*i)--];
	if (is_redir_with_fd(s, *i))
	{
		while (*i >= 0 && ft_isdigit(s[*i]))
			new[(*j)--] = s[(*i)--];
	}
	if (*j >= 0)
		new[(*j)--] = ' ';
}

static int	is_append_back(const char *s, int i)
{
	return (
		s[i] == '>'
		&& !ft_isquoting(s, i + 1)
		&& i - 1 >= 0
		&& s[i - 1] == '>'
	);
}

char	*strdup_with_space_around_redir_op(const char *s)
{
	char	*new;
	int		i;
	int		j;

	i = ft_strlen(s) - 1;
	j = calc_length_with_space_around_redir_op((char *)s);
	new = (char *)wrap_malloc(j + 1);
	new[j--] = '\0';
	while (i >= 0 && j >= 0 && s[i])
	{
		if (is_append_back(s, i) && !is_escaped((char *)s, i - 1))
			add_space_around_append(s, new, &i, &j);
		else if (ft_strchr_quote_escape("<>", s[i]) && !ft_isquoting(s, i + 1)
			&& !is_escaped((char *)s, i))
			add_space_around_trunc_or_input(s, new, &i, &j);
		else
			new[j--] = s[i--];
	}
	return (new);
}
