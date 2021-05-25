#include "minishell.h"

void	*wrap_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		put_error_and_exit();
	return (p);
}
