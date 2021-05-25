#include "minishell.h"

int	is_escaped(char *str, int i)
{
	int	bs;

	bs = 0;
	i--;
	while (i >= 0 && str[i--] == '\\')
		bs++;
	return (bs % 2);
}
