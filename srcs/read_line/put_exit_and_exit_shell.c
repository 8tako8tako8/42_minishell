#include "minishell.h"

void	put_exit_and_exit_shell(t_termcap *tc, t_mini *mini)
{
	tgetent(NULL, tc->env);
	tputs(tc->uninsert, 1, putchar_tc);
	reset_term_config(mini);
	ft_putendl_fd("exit", STDERR);
	exit(mini->ret);
}
