#include "minishell.h"

void	move_cursor_to_right_after_prompt(t_termcap *tc)
{
	tputs(tgoto(tc->move, tc->prompt_size, tc->row), 1, putchar_tc);
}

void	move_cursor_to_left_edge(t_termcap *tc, int lines)
{
	tputs(tgoto(tc->move, 0, tc->row + lines), 1, putchar_tc);
}

void	move_cursor_to_dst(int col, int row, t_termcap *tc)
{
	tputs(tgoto(tc->move, col, row), 1, putchar_tc);
}
