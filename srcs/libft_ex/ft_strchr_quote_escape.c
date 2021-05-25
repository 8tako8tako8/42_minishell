#include "minishell.h"

char	*ft_strchr_quote_escape(char *s, char c)
{
	int	i;
	int	is_escape;

	i = 0;
	is_escape = 0;
	while (s[i])
	{
		if (s[i] == c && !ft_isquoting(s, i + 1) && !is_escape)
			return (s + i);
		if (s[i] == '\\' && !is_escape)
			is_escape = 1;
		else
			is_escape = 0;
		i++;
	}
	return (NULL);
}
