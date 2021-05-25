#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	needle_len = ft_strlen((char *)needle);
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j]
			&& i + j < len && needle[j] == haystack[i + j])
			j++;
		if (j == needle_len)
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
