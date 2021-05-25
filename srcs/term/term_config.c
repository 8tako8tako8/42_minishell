#include "minishell.h"

void	change_term_config(t_mini *mini)
{
	tcgetattr(0, &(mini->oldterm));
	tcgetattr(0, &(mini->term));
	mini->term.c_lflag &= ~ICANON;
	mini->term.c_lflag &= ~ECHO;
	mini->term.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &(mini->term));
}

void	reset_term_config(t_mini *mini)
{
	tcsetattr(0, TCSANOW, &(mini->oldterm));
}
