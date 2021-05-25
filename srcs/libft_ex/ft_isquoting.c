#include "libft_ex.h"

int	ft_isquoting(const char *str, int n)
{
	int	i;
	int	open;

	if (!str)
		return (0);
	i = 0;
	open = 0;
	while (str[i] && i < n)
	{
		if (str[i] == '\\' && str[i + 1] && open != 1)
			i++;
		else if (!open && str[i] == '\'')
			open = 1;
		else if (!open && str[i] == '\"')
			open = 2;
		else if (open == 1 && str[i] == '\'')
			open = 0;
		else if (open == 2 && str[i] == '\"')
			open = 0;
		i++;
	}
	return (open);
}
