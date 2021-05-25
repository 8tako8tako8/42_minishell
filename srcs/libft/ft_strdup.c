#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*str;

	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len] != '\0')
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		str[len] = s1[len];
		len++;
	}
	str[len] = '\0';
	return (str);
}
