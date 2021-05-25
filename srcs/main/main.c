#include "minishell.h"

int		g_sigint;

static void	init_mini(t_mini *mini)
{
	mini->env = NULL;
	mini->command = NULL;
	mini->the_current_working_directory = NULL;
	mini->tmp_in = -1;
	mini->tmp_out = -1;
	mini->tmp_errout = -1;
	mini->saved_fd = ft_calloc(256, sizeof(int));
	mini->pid = -1;
	mini->ret = 0;
}

int	main(void)
{
	t_mini	mini;
	char	*command_line;

	init_mini(&mini);
	init_env(&mini);
	init_history(&mini);
	init_termcap(&mini);
	set_signal_handler_prompt();
	while (1)
	{
		put_prompt();
		init_signal(&mini);
		command_line = read_line(&mini);
		/* if (get_next_line(0, &command_line) < 0)
			return (0); */
		if (parse(&mini, command_line))
		{
			exec_cmdlst(&mini);
			ft_cmdclear(mini.command);
		}
		ft_free((void **)&command_line);
	}
	return (0);
}
