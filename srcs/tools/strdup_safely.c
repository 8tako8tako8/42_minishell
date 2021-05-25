#include "minishell.h"

char	*strdup_safely(const char *str)
{
	char	*ret_str;

	if (str == NULL)
		return (NULL);
	ret_str = ft_strdup(str);
	if (ret_str == NULL)
		put_error_and_exit();
	return (ret_str);
}
