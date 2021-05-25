#include "minishell.h"

int	is_input(char *s, int i)
{
	return (
		s[i] == '<'
		&& !ft_isquoting(s, i)
		&& !is_escaped(s, i)
	);
}
