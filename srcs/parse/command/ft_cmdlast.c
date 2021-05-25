#include "minishell.h"

t_command	*ft_cmdlast(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
