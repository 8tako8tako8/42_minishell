#include "minishell.h"

int	get_history_size(t_history **history)
{
	t_history	*curr_history;
	int			i;

	i = 1;
	curr_history = *history;
	while (curr_history->next != NULL)
	{
		curr_history = curr_history->next;
		i++;
	}
	return (i);
}

void	add_front_new_history(t_history **history, t_history *new_history)
{
	t_history	*curr_history;

	if (!history || !new_history)
		return ;
	if (!*history)
	{
		*history = new_history;
		return ;
	}
	curr_history = *history;
	while (curr_history->prev != NULL)
		curr_history = curr_history->prev;
	curr_history->prev = new_history;
	new_history->next = curr_history;
	*history = new_history;
}

t_history	*create_history(void)
{
	t_history	*new_history;

	new_history = (t_history *)wrap_malloc(sizeof(t_history));
	new_history->str = (char *)wrap_malloc(1);
	new_history->str[0] = '\0';
	new_history->tmp_current_str = NULL;
	new_history->prev = NULL;
	new_history->next = NULL;
	return (new_history);
}

int	init_history(t_mini *mini)
{
	t_history	*new_history;

	new_history = (t_history *)wrap_malloc(sizeof(t_history));
	new_history->str = (char *)wrap_malloc(1);
	new_history->str[0] = '\0';
	new_history->tmp_current_str = NULL;
	new_history->prev = NULL;
	new_history->next = NULL;
	mini->history = new_history;
	return (1);
}
