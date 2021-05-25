#include "minishell.h"

void	*ft_doublelast(void	**p)
{
	void	*ret;

	while (*p)
		ret = *p++;
	return (ret);
}
