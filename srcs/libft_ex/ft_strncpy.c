#include "minishell.h"

void	ft_strncpy(char *dst, char *src, size_t n)
{
	size_t	i;

	if (!src)
		return ;
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dst[i] = src[i];
		i++;
	}
}
