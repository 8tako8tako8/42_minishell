#include "minishell.h"

char	*substr_safely(char const *s, unsigned int start, size_t len)
{
	char	*ret_str;

	ret_str = ft_substr(s, start, len);
	if (ret_str == NULL)
		put_error_and_exit();
	return (ret_str);
}
