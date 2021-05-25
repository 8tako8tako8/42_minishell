/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 01:00:43 by tauehara          #+#    #+#             */
/*   Updated: 2021/05/16 19:00:00 by tauehara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*p;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (!(p = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(p, str, len + 1);
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *p;
	char *ret;

	if (!s1 || !s2)
		return (NULL);
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ret = p;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return (ret);
}
