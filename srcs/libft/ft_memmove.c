#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t					i;
	unsigned char			*dst1;
	const unsigned char		*src1;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	dst1 = (unsigned char *)dst;
	src1 = (const unsigned char *)src;
	i = len;
	while (i > 0)
	{
		dst1[i - 1] = src1[i - 1];
		i--;
	}
	return (dst);
}
