#include "minishell.h"

void	**ft_doubleadd_back(void **p, void *new)
{
	void	**ret;
	size_t	i;

	ret = (void **)malloc(sizeof(void *) * (ft_doublesize(p) + 2));
	i = 0;
	while (*p)
	{
		ret[i] = ft_strdup(*p);
		if (ret[i++] == NULL)
			return (NULL);
		p++;
	}
	ret[i++] = new;
	ret[i] = NULL;
	return (ret);
}
