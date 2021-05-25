#include "minishell.h"

static char	**allocate_splitted_num(int splitted_num)
{
	char	**dst;

	dst = (char **)wrap_malloc(sizeof(char *) * (splitted_num + 1));
	return (dst);
}

static int	count_splitted_num(char const *s, char c)
{
	int		count;
	int		i;

	count = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	**split_path(char *s)
{
	char	**dst;
	int		splitted_num;

	splitted_num = count_splitted_num(s, ':');
	dst = allocate_splitted_num(splitted_num);
	dst = split_str(dst, s, splitted_num);
	return (dst);
}
