#include "minishell.h"

int	calc_length_with_space_around_redir_op(char *s)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (is_append(s, i))
		{
			i++;
			count++;
		}
		else if (is_trunc(s, i) || is_input(s, i))
			count++;
		i++;
	}
	return (i + 2 * count);
}
