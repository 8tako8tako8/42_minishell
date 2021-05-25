#include "minishell.h"

int	ft_is_quotedstr(char *s, int quote_type)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_isquoting(s, i + 1) == quote_type)
			return (1);
		i++;
	}
	return (0);
}
