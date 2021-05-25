#include "minishell.h"

void	ft_tokenclear(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		free(token->str);
		tmp = token;
		token = token->next;
		free(tmp);
	}
}
