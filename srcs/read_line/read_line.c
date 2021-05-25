#include "minishell.h"

static void	reset_entering_command(t_termcap *tc, t_history **moved_hist,
	t_mini *mini)
{
	*moved_hist = mini->history;
	get_cursor_position(tc);
	free(mini->history->str);
	mini->history->str = (char *)wrap_malloc(1);
	mini->history->str[0] = '\0';
	if (mini->history->tmp_current_str != NULL)
	{
		free(mini->history->tmp_current_str);
		mini->history->tmp_current_str = NULL;
	}
	mini->ret = 1;
	g_sigint = 0;
}

static void	check_sigint(t_termcap *tc, t_history **moved_hist, t_mini *mini)
{
	if (g_sigint)
		reset_entering_command(tc, moved_hist, mini);
}

static char	*read_char_in_loop(t_mini *mini)
{
	t_history	*moved_hist;
	int			c;
	int			res_key;

	moved_hist = mini->history;
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		check_sigint(&mini->tc, &moved_hist, mini);
		check_term_size(&mini->tc);
		res_key = divide_cases_by_key(c, &moved_hist, mini);
		c = 0;
		if (res_key == CONTINUE_INPUT)
			continue ;
		else if (res_key == FINISH_INPUT)
			return (strdup_safely(mini->history->next->str));
		else if (res_key == ONLY_NULL_CHAR)
			return (strdup_safely(mini->history->str));
		else if (res_key == EXIT_SHELL)
			put_exit_and_exit_shell(&mini->tc, mini);
	}
	return (NULL);
}

char	*read_line(t_mini *mini)
{
	change_term_config(mini);
	set_insert_mode(&mini->tc);
	get_cursor_position(&mini->tc);
	get_term_size(&mini->tc);
	return (read_char_in_loop(mini));
}
