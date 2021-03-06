#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*head;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (!*s1)
		return (ft_strdup(s1));
	head = (char *)s1;
	while (*(s1 + 1))
		s1++;
	while (ft_strchr(set, *s1))
		s1--;
	return (ft_substr(head, 0, s1 - head + 1));
}
