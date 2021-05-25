#include "minishell.h"

t_redirect	*ft_redirnew(int fd_io, int type, char *file)
{
	t_redirect	*new;

	new = wrap_malloc(sizeof(t_redirect));
	new->fd_io = fd_io;
	new->type = type;
	new->before_expand = NULL;
	new->file = file;
	new->next = NULL;
	new->fd_open = -1;
	return (new);
}
