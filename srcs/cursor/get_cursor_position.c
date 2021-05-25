#include "minishell.h"

static void	get_row_or_col(char *buf, t_termcap *tc, int *row_flag, int *i)
{
	if (*row_flag == 0)
	{
		tc->row = ft_atoi(&buf[*i]) - 1;
		while (ft_isdigit(buf[*i]))
			(*i)++;
		*row_flag = 1;
	}
	else
	{
		tc->col = ft_atoi(&buf[*i]) - 1;
		tc->prompt_size = tc->col;
		while (ft_isdigit(buf[*i]))
			(*i)++;
	}
}

void	get_cursor_position(t_termcap *tc)
{
	int		row_flag;
	int		i;
	char	buf[255];
	int		ret;

	row_flag = 0;
	i = 1;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (ft_isdigit(buf[i]))
			get_row_or_col(buf, tc, &row_flag, &i);
		i++;
	}
}

int	get_cursor_row_position(void)
{
	int		i;
	char	buf[255];
	int		ret;
	int		row;

	i = 1;
	row = 0;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (ft_isdigit(buf[i]))
		{
			row = ft_atoi(&buf[i]) - 1;
			break ;
		}
		i++;
	}
	return (row);
}
