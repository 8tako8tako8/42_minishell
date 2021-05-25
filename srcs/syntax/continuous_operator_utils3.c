#include "minishell.h"

int	is_pipes_error(char *str, int i, char prev_op)
{
	return (
		(
			str[i]
			&& prev_op == '|'
			&& str[i] == '|'
			&& str[i - 1] == '|'
		) || (
			str[i]
			&& str[i] == '|'
			&& str[i + 1]
			&& str[i + 1] == '|'
		)
	);
}

int	is_ends_error(char *str, int i, char prev_op)
{
	return (
		(
			str[i]
			&& prev_op == ';'
			&& str[i] == ';'
			&& str[i - 1] == ';'
		) || (
			str[i]
			&& str[i] == ';'
			&& str[i + 1]
			&& str[i + 1] == ';'
		)
	);
}

int	is_inputs_error(char *str, int i, char prev_op)
{
	return (
		(
			str[i]
			&& prev_op == '<'
			&& str[i] == '<'
			&& str[i - 1] == '<'
		) || (
			str[i]
			&& str[i] == '<'
			&& str[i + 1]
			&& str[i + 1] == '<'
		)
	);
}

int	is_append_error(char *str, int i, char prev_op)
{
	return (
		str[i]
		&& prev_op
		&& str[i] == '>'
		&& str[i + 1]
		&& str[i + 1] == '>'
	);
}
