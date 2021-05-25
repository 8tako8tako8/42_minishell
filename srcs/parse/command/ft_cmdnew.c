#include "minishell.h"

t_command	*ft_cmdnew(int argc, char **argv, int op, t_redirect *redirect)
{
	t_command	*new;

	new = wrap_malloc(sizeof(t_command));
	new->argc = argc;
	new->argv = argv;
	new->op = op;
	new->redirect = redirect;
	new->next = NULL;
	return (new);
}
