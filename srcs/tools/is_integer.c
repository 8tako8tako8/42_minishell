#include "minishell.h"

int	is_integer(int sign, char *nbr)
{
	int	digit;

	while (*nbr == '0')
		nbr++;
	digit = 0;
	while (ft_isdigit(nbr[digit]))
		digit++;
	if (digit > 10)
		return (0);
	if (sign == 1 && ft_strncmp(nbr, "2147483647", 10) > 0 && digit == 10)
		return (0);
	if (sign == -1 && ft_strncmp(nbr, "2147483648", 10) > 0 && digit == 10)
		return (0);
	return (1);
}
