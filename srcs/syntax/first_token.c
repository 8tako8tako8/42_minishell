#include "minishell.h"

int	validate_first_token(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			;
		else if (ft_strchr(";|", str[i]))
			break ;
		else
			return (VALID);
		i++;
	}
	if (str[i] == '|' && str[i] && str[i + 1] == '|')
		return (ERR_PIPES);
	else if (str[i] == '|')
		return (ERR_PIPE);
	else if (str[i] == ';' && str[i] && str[i + 1] == ';')
		return (ERR_ENDS);
	else if (str[i] == ';')
		return (ERR_END);
	return (VALID);
}
