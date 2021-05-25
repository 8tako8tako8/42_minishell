#include "minishell.h"

static int	strlen_escaped(const char *value)
{
	int		strlen;
	int		i;

	strlen = 0;
	i = 0;
	while (value[i])
	{
		if (ft_strchr("$`\"\\", value[i]) != NULL)
			strlen++;
		strlen++;
		i++;
	}
	return (strlen);
}

char	*escape_str(char *value)
{
	char	*ret_str;
	int		i;
	int		escape_i;

	ret_str = (char *)wrap_malloc(strlen_escaped(value) + 1);
	i = 0;
	escape_i = 0;
	while (value[i])
	{
		if (ft_strchr("$`\"\\", value[i]) != NULL)
		{
			ret_str[escape_i] = '\\';
			escape_i++;
		}
		ret_str[escape_i] = value[i];
		escape_i++;
		i++;
	}
	ret_str[escape_i] = '\0';
	return (ret_str);
}
