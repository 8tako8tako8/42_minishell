#include "minishell.h"

void	ft_tokenadd_back(t_token **token, t_token *new)
{
	if (!*token)
	{
		*token = new;
		return ;
	}
	ft_tokenlast(*token)->next = new;
}
