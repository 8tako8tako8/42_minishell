#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		s_len;
	char		*dst;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if ((s_len == 0) || (s_len < (size_t)start))
		return (ft_strdup(""));
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (len == SIZE_MAX || dst == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
