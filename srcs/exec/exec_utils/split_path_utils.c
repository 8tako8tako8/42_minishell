#include "minishell.h"

static void	copy_path(char **dst, int j, char *s, int *i)
{
	int		k;

	k = 0;
	while (s[*i] != '\0' && s[*i] != ':')
	{
		dst[j][k] = s[*i];
		k++;
		(*i)++;
	}
	dst[j][k] = '\0';
	if (s[*i] != '\0')
		(*i)++;
}

static char	*allocate_str(char **dst, int j, int size)
{
	dst[j] = (char *)wrap_malloc(size + 1);
	return (dst[j]);
}

static void	copy_curr_dir(char **dst, int j, char *curr_dir, int *i)
{
	dst[j] = strdup_safely(curr_dir);
	(*i)++;
}

static int	str_size(char const *s, char c, int i)
{
	int		size;

	size = 0;
	while (s[i] != c && s[i] != '\0')
	{
		size++;
		i++;
	}
	return (size);
}

char	**split_str(char **dst, char *s, int splitted_num)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < splitted_num)
	{
		size = str_size(s, ':', i);
		if (size == 0)
			copy_curr_dir(dst, j, ".", &i);
		else
		{
			dst[j] = allocate_str(dst, j, size);
			copy_path(dst, j, s, &i);
		}
		j++;
	}
	if (s[i - 1] == ':')
	{
		copy_curr_dir(dst, j, ".", &i);
		j++;
	}
	dst[j] = NULL;
	return (dst);
}
