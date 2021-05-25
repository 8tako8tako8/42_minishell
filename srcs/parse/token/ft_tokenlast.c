#include "minishell.h"

t_token	*ft_tokenlast(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}
