#include "minishell.h"

static void	flush_line_after_prompt(t_termcap *tc)
{
	move_cursor_to_right_after_prompt(tc);
	flush_line_after_cursor(tc);
}

static void	flush_line(t_termcap *tc, int lines)
{
	move_cursor_to_left_edge(tc, lines);
	flush_line_after_cursor(tc);
}

void	flush_current_line(t_termcap *tc, int strlen)
{
	int		lines;

	if (is_multiline(tc, strlen))
	{
		lines = calc_num_of_lines(tc, strlen);
		while (lines > 0)
		{
			flush_line(tc, lines);
			lines--;
		}
		flush_line_after_prompt(tc);
	}
	else
		flush_line_after_prompt(tc);
}
