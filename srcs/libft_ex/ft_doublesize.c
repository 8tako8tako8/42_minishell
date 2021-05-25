#include "minishell.h"

size_t	ft_doublesize(void **p)
{
	size_t	len;

	if (!p)
		return (0);
	len = 0;
	while (*p++)
		len++;
	return (len);
}
