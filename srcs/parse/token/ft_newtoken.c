#include "minishell.h"

t_token	*ft_newtoken(int type, char *str)
{
	t_token	*new;

	new = (t_token *)wrap_malloc(sizeof(t_token));
	new->type = type;
	new->str = str;
	new->next = NULL;
	return (new);
}
