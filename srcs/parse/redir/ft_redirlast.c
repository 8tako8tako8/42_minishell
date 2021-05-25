#include "minishell.h"

t_redirect	*ft_redirlast(t_redirect *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}
