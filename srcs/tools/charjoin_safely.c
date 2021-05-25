#include "minishell.h"

char	*charjoin_safely(const char *s, char c)
{
	char	*p;

	p = ft_charjoin(s, c);
	if (!p)
		put_error_and_exit();
	return (p);
}
