#include "minishell.h"

void	ft_cmdclear(t_command *cmd)
{
	t_command	*tmp_cmd;

	if (!cmd)
		return ;
	while (cmd)
	{
		ft_free_double((void ***)&cmd->argv);
		ft_redirclear(cmd->redirect);
		tmp_cmd = cmd;
		cmd = cmd->next;
		free(tmp_cmd);
	}
}
