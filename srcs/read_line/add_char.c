#include "minishell.h"

static void	move_cursor_to_newline(t_termcap *tc, int strlen)
{
	int		lines;
	int		dst_col;
	int		dst_row;

	lines = calc_num_of_lines(tc, strlen);
	dst_row = tc->row + lines;
	dst_col = 0;
	if (is_cursor_bottom_multiline(tc, lines))
		write(STDOUT, "\n", 1);
	move_cursor_to_dst(dst_col, dst_row, tc);
}

static void	add_char_in_history(t_history **history, char c, int col)
{
	char	*tmp;
	int		strlen;

	tmp = (*history)->str;
	strlen = ft_strlen((*history)->str);
	(*history)->str = (char *)wrap_malloc(strlen + 2);
	ft_strncpy((*history)->str, tmp, col);
	(*history)->str[col] = c;
	ft_strncpy((*history)->str + col + 1, tmp + col, strlen - col);
	(*history)->str[strlen + 1] = '\0';
	free(tmp);
}

int	add_char(int c, t_termcap *tc, t_history **history)
{
	(tc->col)++;
	write(1, &c, 1);
	if (is_cursor_right_edge(tc))
		move_cursor_to_newline(tc, ft_strlen((*history)->str) + 1);
	calc_prompt_position_input(tc, history);
	add_char_in_history(history, (char)c, tc->col - tc->prompt_size - 1);
	return (CONTINUE_INPUT);
}
