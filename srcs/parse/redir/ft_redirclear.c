#include "minishell.h"

void	ft_redirclear(t_redirect *redir)
{
	t_redirect	*tmp;

	if (!redir)
		return ;
	while (redir)
	{
		if (redir->file)
			free(redir->file);
		if (redir->before_expand)
			free(redir->before_expand);
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
}
