#include "minishell.h"

void	flush_line_after_cursor(t_termcap *tc)
{
	tputs(tc->flush_line, 1, putchar_tc);
}

void	flush_char(t_termcap *tc)
{
	tputs(tc->flush_char, 1, putchar_tc);
}
