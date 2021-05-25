#include "minishell.h"

void	**ft_doubledup(void	**p)
{
	void	**ret;
	size_t	i;

	ret = (void **)malloc(sizeof(void *) * (ft_doublesize(p) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (*p)
	{
		ret[i] = ft_strdup(*p++);
		if (ret[i++] == NULL)
		{
			ft_free_double((void ***)&ret);
			return (NULL);
		}
	}
	ret[i] = NULL;
	return (ret);
}
