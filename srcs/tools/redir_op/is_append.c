#include "minishell.h"

int	is_append(char *s, int i)
{
	return (
		s[i] == '>'
		&& !ft_isquoting(s, i + 1)
		&& s[i + 1]
		&& s[i + 1] == '>'
		&& !is_escaped(s, i)
	);
}
