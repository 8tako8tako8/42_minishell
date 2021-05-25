#include "minishell.h"

int	is_multiline(t_termcap *tc, int strlen)
{
	return (tc->prompt_size + strlen > tc->col_size);
}
