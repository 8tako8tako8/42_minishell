#include "minishell.h"

int	validate_last_character(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i >=0 && str[i] == '\\' && !is_escaped(str, i))
		return (ERR_NEWLINE);
	return (VALID);
}
