#include "minishell.h"

int	validate_last_token(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0 && str[i] == ' ')
		i--;
	if (ft_strchr("|<>", str[i]) && !is_escaped(str, i))
		return (ERR_NEWLINE);
	return (VALID);
}
