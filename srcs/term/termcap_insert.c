#include "minishell.h"

void	set_insert_mode(t_termcap *tc)
{
	tputs(tc->insert, 1, putchar_tc);
}

void	unset_insert_mode(t_termcap *tc)
{
	tputs(tc->uninsert, 1, putchar_tc);
}
