#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		srcsize;

	if (!src)
		return (0);
	srcsize = 0;
	while (src[srcsize])
		srcsize++;
	if (dstsize == 0)
		return (srcsize);
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srcsize);
}
