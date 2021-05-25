#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return ((t_uchar)(*s1) - (t_uchar)(*s2));
}
