#include "libft_ex.h"

void	ft_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
}
