#include "minishell.h"

void	put_prompt(void)
{
	if (g_sigint == 0)
		ft_putstr_fd(PROMPT, STDERR);
}
