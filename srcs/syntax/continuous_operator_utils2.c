#include "minishell.h"

int	is_control_op_continuous(char *str, int *i, char *prev_op, int *is_fd)
{
	return (
		ft_strchr(";|", str[*i])
		&& !ft_isquoting(str, *i + 1)
		&& *prev_op
		&& !*is_fd
	);
}

int	is_append_syntax(char *str, int *i)
{
	return (
		str[*i] == '>'
		&& *i > 0
		&& str[*i - 1] == '>'
		&& !ft_isquoting(str, *i + 1)
		&& (
			*i - 1 == 0
			|| (
				*i - 1 > 0
				&& !is_escaped(str, *i - 2)
			)
		)
	);
}

int	is_redirection_op_continuous(char *str, int *i, char *prev_op)
{
	return (
		(
			ft_strchr("<>", str[*i])
			&& !ft_isquoting(str, *i + 1)
			&& *prev_op
			&& ft_strchr("<>", *prev_op)
			&& !is_append_syntax(str, i)
		) || (
			*prev_op == 'A'
			&& ft_strchr("<>", str[*i])
			&& !ft_isquoting(str, *i + 1)
		)
	);
}

void	reset_prev_op_and_is_redir_fd(char *prev_op, int *is_redir_fd)
{
	*prev_op = '\0';
	*is_redir_fd = 0;
}
