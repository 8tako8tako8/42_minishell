#include "minishell.h"

static int	is_cursor_bottom(t_termcap *tc)
{
	return (tc->row == (tc->row_size - 1));
}

int	is_cursor_bottom_multiline(t_termcap *tc, int lines)
{
	return (tc->row + lines >= (tc->row_size - 1));
}

int	calc_num_of_lines(t_termcap *tc, int strlen)
{
	return (((tc->prompt_size + strlen - tc->col_size) / tc->col_size) + 1);
}

void	calc_prompt_position_history(t_termcap *tc, int strlen)
{
	int		lines;

	tc->col = tc->prompt_size + strlen;
	if (is_multiline(tc, strlen))
	{
		lines = calc_num_of_lines(tc, strlen);
		if (is_cursor_bottom_multiline(tc, lines))
			tc->row = get_cursor_row_position() - lines;
	}
}

void	calc_prompt_position_input(t_termcap *tc, t_history **history)
{
	int		strlen;
	int		lines;

	strlen = ft_strlen((*history)->str);
	if (is_multiline(tc, strlen))
	{
		lines = calc_num_of_lines(tc, strlen);
		if (is_cursor_right_edge(tc) && is_cursor_bottom_multiline(tc, lines))
			tc->row = get_cursor_row_position() - lines - 1;
	}
	else
	{
		if (is_cursor_right_edge(tc) && is_cursor_bottom(tc))
			tc->row = get_cursor_row_position() - 1;
	}
}
