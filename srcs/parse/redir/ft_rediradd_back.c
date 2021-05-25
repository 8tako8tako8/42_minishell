#include "minishell.h"

void	ft_rediradd_back(t_redirect **redir, t_redirect *new)
{
	if (!*redir)
	{
		*redir = new;
		return ;
	}
	ft_redirlast(*redir)->next = new;
}
