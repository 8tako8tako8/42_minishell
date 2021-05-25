#include "minishell.h"

void	**ft_doublejoin(void **p1, void **p2)
{
	void	**d1;
	void	**d2;
	void	**ret;

	ret = (void **)malloc(
			sizeof(void *) * (ft_doublesize(p1) + ft_doublesize(p2) + 1));
	*ret = NULL;
	d1 = ft_doubledup(p1);
	if (d1 == NULL)
	{
		ft_free_double((void ***)&ret);
		return (NULL);
	}
	ft_doublecat(ret, d1);
	d2 = ft_doubledup(p2);
	if (d2 == NULL)
	{
		ft_free_double((void ***)&ret);
		return (NULL);
	}
	ft_doublecat(ret, d2);
	free(d1);
	free(d2);
	return (ret);
}
