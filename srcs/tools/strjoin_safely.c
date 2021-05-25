#include "minishell.h"

char	*strjoin_safely(char const *s1, char const *s2)
{
	char	*ret_str;

	ret_str = ft_strjoin(s1, s2);
	if (ret_str == NULL)
		put_error_and_exit();
	return (ret_str);
}
