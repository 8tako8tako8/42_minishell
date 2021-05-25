#include "minishell.h"

void	get_term_size(t_termcap *tc)
{
	tc->row_size = get_term_row_size();
	tc->col_size = get_term_col_size();
}

int	get_term_row_size(void)
{
	struct winsize	winsize;

	ioctl(1, TIOCGWINSZ, &winsize);
	return ((int)winsize.ws_row);
}

int	get_term_col_size(void)
{
	struct winsize	winsize;

	ioctl(1, TIOCGWINSZ, &winsize);
	return ((int)winsize.ws_col);
}
