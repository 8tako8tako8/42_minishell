#include "minishell.h"

void	ft_free_double(void ***p)
{
	int		i;
	void	**tmp;

	tmp = *p;
	if (tmp)
	{
		i = 0;
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		tmp = NULL;
	}
}
