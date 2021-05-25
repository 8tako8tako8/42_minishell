#include "minishell.h"

void	**ft_doublemap(void **old, char *(*f)(char *))
{
	void	**new;
	size_t	i;
	void	*elem;

	new = malloc(sizeof(void *) * (ft_doublesize(old) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		elem = f(old[i]);
		if (!elem)
			ft_free_double((void ***)&new);
		new[i] = elem;
		i++;
	}
	new[i] = NULL;
	return (new);
}
