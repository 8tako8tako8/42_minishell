#include "minishell.h"

char	*get_char_of_open_quotes_error(int quote_type)
{
	if (quote_type == DQUOTE)
		return (DQUOTE_STR);
	else if (quote_type == SQUOTE)
		return (SQUOTE_STR);
	return (NULL);
}
