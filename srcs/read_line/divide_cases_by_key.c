#include "minishell.h"

int	divide_cases_by_key(int c, t_history **moved_hist, t_mini *mini)
{
	if (c == UP_ARROW)
		return (move_previous_history(&mini->tc, &mini->history, moved_hist));
	else if (c == DOWN_ARROW)
		return (move_next_history(&mini->tc, &mini->history, moved_hist));
	else if ((c == CTRL_D) && (ft_strlen(mini->history->str) == 0))
		return (EXIT_SHELL);
	else if (c == CTRL_D || c == LEFT_ARROW || c == RIGHT_ARROW || c == TAB_KEY)
		return (CONTINUE_INPUT);
	else if (c == BACK_SPACE)
		return (delete_char(&mini->tc, &mini->history));
	else if (c == NEW_LINE)
		return (finish_command_reading(c, &mini->tc, &mini->history, mini));
	else
		return (add_char(c, &mini->tc, &mini->history));
}
