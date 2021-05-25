#include "minishell.h"

char	*ft_charjoin(const char *s, char c)
{
	char	*p;
	int		i;

	p = malloc(ft_strlen(s) + 2);
	if (!p)
		return (NULL);
	i = 0;
	while (*s)
		p[i++] = *s++;
	p[i++] = c;
	p[i] = '\0';
	return (p);
}
