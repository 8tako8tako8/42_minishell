#include "minishell.h"

void	init_signal(t_mini *mini)
{
	mini->sigint_flag = g_sigint;
	g_sigint = 0;
}

static void	deal_with_signal_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(PROMPT, STDERR);
		g_sigint = 1;
	}
}

void	set_signal_handler_prompt(void)
{
	signal(SIGINT, &deal_with_signal_prompt);
	signal(SIGQUIT, &deal_with_signal_prompt);
	g_sigint = 0;
}

static void	deal_with_signal_no_prompt(int signum)
{
	(void)signum;
/* 	if (signum == SIGINT)
		g_sigint = 1; */
}

void	set_signal_handler_no_prompt(void)
{
	signal(SIGINT, &deal_with_signal_no_prompt);
	signal(SIGQUIT, &deal_with_signal_no_prompt);
	g_sigint = 0;
}
