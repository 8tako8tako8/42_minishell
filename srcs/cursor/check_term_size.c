#include "minishell.h"

static void	calc_prompt_position(t_termcap *tc)
{
	int		lines;

	if (tc->col + 1 <= tc->col_size)
		tc->row = get_cursor_row_position();
	else
	{
		lines = ((tc->col + 1 - tc->col_size) / tc->col_size) + 1;
		tc->row = get_cursor_row_position() - lines;
	}
}

void	check_term_size(t_termcap *tc)
{
	int		row_size;
	int		col_size;

	row_size = get_term_row_size();
	col_size = get_term_col_size();
	if (tc->row_size != row_size || tc->col_size != col_size)
	{
		tc->row_size = row_size;
		tc->col_size = col_size;
		calc_prompt_position(tc);
	}
}
