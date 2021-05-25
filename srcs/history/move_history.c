#include "minishell.h"

int	move_previous_history(t_termcap *tc, t_history **history,
	t_history **moved_hist)
{
	char	*new_str;

	if ((*moved_hist)->next == NULL)
		return (CONTINUE_INPUT);
	flush_current_line(tc, ft_strlen((*history)->str));
	*moved_hist = (*moved_hist)->next;
	new_str = get_history_str(HISTORY_BACK, history, moved_hist);
	free((*history)->str);
	(*history)->str = new_str;
	ft_putstr_fd(new_str, STDOUT);
	calc_prompt_position_history(tc, ft_strlen(new_str));
	return (CONTINUE_INPUT);
}

int	move_next_history(t_termcap *tc, t_history **history,
	t_history **moved_hist)
{
	char	*new_str;

	if ((*moved_hist)->prev == NULL)
		return (CONTINUE_INPUT);
	flush_current_line(tc, ft_strlen((*history)->str));
	*moved_hist = (*moved_hist)->prev;
	new_str = get_history_str(HISTORY_FORWARD, history, moved_hist);
	free((*history)->str);
	(*history)->str = new_str;
	ft_putstr_fd(new_str, STDOUT);
	calc_prompt_position_history(tc, ft_strlen(new_str));
	return (CONTINUE_INPUT);
}
