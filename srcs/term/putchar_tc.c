#include "minishell.h"

int	putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}
