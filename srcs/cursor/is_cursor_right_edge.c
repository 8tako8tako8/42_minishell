#include "minishell.h"

int	is_cursor_right_edge(t_termcap *tc)
{
	return (tc->col % tc->col_size == 0);
}
