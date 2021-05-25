#include "minishell.h"

static void	move_cursor_to_left_one(t_termcap *tc)
{
	(tc->col)--;
	move_cursor_to_dst(tc->col, tc->row, tc);
}

static void	move_cursor_to_left_one_multiline(t_termcap *tc, int strlen)
{
	int		lines;
	int		dst_col;
	int		dst_row;

	lines = calc_num_of_lines(tc, strlen);
	dst_row = tc->row;
	if (is_cursor_right_edge(tc))
		dst_row += lines - 1;
	else
		dst_row += lines;
	(tc->col)--;
	dst_col = tc->col % tc->col_size;
	move_cursor_to_dst(dst_col, dst_row, tc);
}

static void	delete_char_in_term(t_termcap *tc, int strlen)
{
	if (is_multiline(tc, strlen))
	{
		move_cursor_to_left_one_multiline(tc, strlen);
		flush_char(tc);
	}
	else
	{
		move_cursor_to_left_one(tc);
		flush_char(tc);
	}
}

static void	delete_char_in_history(t_history **history, int dstcol)
{
	char	*tmp;
	int		strlen;

	tmp = (*history)->str;
	strlen = ft_strlen((*history)->str);
	(*history)->str = (char *)wrap_malloc(sizeof(char) * strlen);
	ft_strncpy((*history)->str, tmp, dstcol);
	ft_strncpy((*history)->str + dstcol, tmp + dstcol + 1, strlen - dstcol - 1);
	(*history)->str[strlen - 1] = '\0';
	free(tmp);
}

int	delete_char(t_termcap *tc, t_history **history)
{
	if (tc->col != tc->prompt_size)
	{
		delete_char_in_term(tc, ft_strlen((*history)->str));
		delete_char_in_history(history, tc->col - tc->prompt_size);
	}
	return (CONTINUE_INPUT);
}
