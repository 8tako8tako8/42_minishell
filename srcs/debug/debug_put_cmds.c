#include "minishell.h"

void	put_cmds(t_command *cmd)
{
	int i;
	t_redirect	*redir;

	if (!cmd)
		return ;
	
	printf("[CMD]\n");
	while (cmd)
	{
		i = 0;
		printf("========================================\n");
		printf(" argc  : %d\n", cmd->argc);
		printf(" argv  : ");
		while (cmd->argv[i])
		{
			printf("%s", cmd->argv[i++]);
			if (cmd->argv[i])
				printf(", ");
		}
		printf("\n");
		printf(" op    : ");	
		if (cmd->op == 0)
			printf("NORMAL (0)\n");
		else
			printf("PIPE (1)\n");
		printf(" redir :\n");
		redir = cmd->redirect;
		while (redir)
		{
			printf("         fd_io : %d\n", redir->fd_io);
			if (redir->type == 0)
				printf("         type  : INPUT (\"<\" : 0)\n");
			else if (redir->type == 1)
				printf("         type  : TRUNC (\">\" : 1)\n");
			else if (redir->type == 2)
				printf("         type  : APPEND(\">>\" : 2)\n");
			if (*(redir->file) == -1)
				printf("         file  : (ambiguous)\n");
			else
				printf("         file  : %s\n", redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
