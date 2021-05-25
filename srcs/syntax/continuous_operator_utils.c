#include "minishell.h"

int	get_fd(char *s, int i, int *ret)
{
	if (!ft_isdigit(s[i]))
		return (0);
	while (i >= 0 && ft_isdigit(s[i]))
		i--;
	if (!is_integer(1, s + i + 1))
	{
		*ret = ERR_FD_OVERFLOW;
		return (1);
	}
	*ret = ft_atoi(s + i + 1);
	return (1);
}

int	set_error_type(int *ret, int errtype)
{
	*ret = errtype;
	return (INVALID);
}

int	set_error_type_redir(int *ret, int errtype, char *str, int i)
{
	if (i - 1 >= 0 && get_fd(str, i - 1, ret))
		;
	else
		*ret = errtype;
	return (INVALID);
}

int	set_error_type_inputs(int *ret, int errtype, char *str, int i)
{
	if (i - 2 >= 0 && get_fd(str, i - 2, ret))
		;
	else
		*ret = errtype;
	return (INVALID);
}
