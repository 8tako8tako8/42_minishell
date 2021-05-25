#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t				i;
	unsigned char		*buf;

	i = 0;
	buf = (unsigned char *)b;
	while (i < len)
	{
		buf[i] = c;
		i++;
	}
	return (b);
}
