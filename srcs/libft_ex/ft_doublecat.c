#include "minishell.h"

void	**ft_doublecat(void	**dst, void **src)
{
	size_t	i;

	i = 0;
	while (dst[i])
		i++;
	while (*src)
		dst[i++] = *src++;
	dst[i] = NULL;
	return (dst);
}
