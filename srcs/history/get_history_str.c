#include "minishell.h"

static char	*get_tmp_current_str(t_history **history)
{
	char	*ret_str;

	ret_str = strdup_safely((*history)->tmp_current_str);
	free((*history)->tmp_current_str);
	(*history)->tmp_current_str = NULL;
	return (ret_str);
}

static void	store_entering_command(t_history **history)
{
	(*history)->tmp_current_str = strdup_safely((*history)->str);
}

static int	is_unregistered_history(t_history **moved_hist)
{
	return ((*moved_hist)->prev == NULL);
}

static int	is_latest_history(t_history **moved_hist)
{
	return ((*moved_hist)->prev->prev == NULL);
}

char	*get_history_str(int key, t_history **history, t_history **moved_hist)
{
	if (key == HISTORY_BACK && is_latest_history(moved_hist))
		store_entering_command(history);
	if (key == HISTORY_FORWARD && is_unregistered_history(moved_hist))
		return (get_tmp_current_str(history));
	return (strdup_safely((*moved_hist)->str));
}
