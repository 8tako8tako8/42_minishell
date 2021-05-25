#include "minishell.h"

int	identify_type_of_continuous_violation(char *str, int i,
											char prev_op, int *ret)
{
	if (is_pipes_error(str, i, prev_op))
		return (set_error_type(ret, ERR_PIPES));
	else if (is_ends_error(str, i, prev_op))
		return (set_error_type(ret, ERR_ENDS));
	else if (is_inputs_error(str, i, prev_op))
		return (set_error_type_inputs(ret, ERR_INPUTS, str, i));
	else if (is_append_error(str, i, prev_op))
		return (set_error_type_redir(ret, ERR_APPEND, str, i));
	else if (str[i] == '|')
		return (set_error_type(ret, ERR_PIPE));
	else if (str[i] == ';')
		return (set_error_type(ret, ERR_END));
	else if (str[i] == '<')
		return (set_error_type_redir(ret, ERR_INPUT, str, i));
	else if (str[i] == '>')
		return (set_error_type_redir(ret, ERR_TRUNC, str, i));
	return (VALID);
}

void	read_through_until_find_continuous(char *str, int *i, char *prev_op)
{
	int	is_redir_fd;

	is_redir_fd = 0;
	while (str[*i])
	{
		if (str[*i] == ' ' && !is_redir_fd)
			;
		else if (str[*i] == '\\' && str[*i + 1] && ++(*i))
			*prev_op = '\0';
		else if (ft_isdigit(str[*i]) && *prev_op && !ft_isquoting(str, *i + 1))
			is_redir_fd = 1;
		else if (is_control_op_continuous(str, i, prev_op, &is_redir_fd))
			break ;
		else if (is_redirection_op_continuous(str, i, prev_op))
			break ;
		else if (is_append_syntax(str, i))
			*prev_op = 'A';
		else if (ft_strchr(";|<>", str[*i]) && !ft_isquoting(str, *i + 1))
			*prev_op = str[*i];
		else
			reset_prev_op_and_is_redir_fd(prev_op, &is_redir_fd);
		(*i)++;
	}
}

int	validate_continuous_operator(char *str, int *ret)
{
	int		i;
	char	prev_op;

	i = 0;
	prev_op = '\0';
	read_through_until_find_continuous(str, &i, &prev_op);
	return (identify_type_of_continuous_violation(str, i, prev_op, ret));
}
