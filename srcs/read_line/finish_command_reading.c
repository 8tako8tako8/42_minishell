#include "minishell.h"

static void	update_history(t_history **history)
{
	t_history	*new_history;

	new_history = create_history();
	add_front_new_history(history, new_history);
}

int	finish_command_reading(int c, t_termcap *tc, t_history **history,
	t_mini *mini)
{
	write(1, &c, 1);
	unset_insert_mode(tc);
	reset_term_config(mini);
	if (ft_strlen((*history)->str) == 0)
		return (ONLY_NULL_CHAR);
	update_history(history);
	return (FINISH_INPUT);
}
