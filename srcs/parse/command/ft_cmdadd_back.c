#include "minishell.h"

void	ft_cmdadd_back(t_command **cmd, t_command *new)
{
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	ft_cmdlast(*cmd)->next = new;
}
