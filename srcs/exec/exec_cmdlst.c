#include "minishell.h"

static int	wait_child_proc(t_mini *mini)
{
	int		status;
	int		signum;
	int		tmp_status;
	int		i;

	waitpid(mini->pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		status = 128 + signum;
		if (signum == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR);
		if (signum == SIGINT)
			ft_putstr_fd("\n", STDERR);
	}
	i = 0;
	while (waitpid(-1, &tmp_status, 0) > 0)
	{
		if (i++ == 0 && WIFSIGNALED(tmp_status) && WTERMSIG(tmp_status) == SIGINT)
			ft_putstr_fd("\n", STDERR);
	}
	set_signal_handler_prompt();
	return (status);
}

static int	has_exit_error(t_mini *mini)
{
	return (mini->exit_error);
}

void	exec_cmdlst(t_mini *mini)
{
	t_command	*curr_cmd;
	char		**tmp;

	mini->exit_error = 0;
	curr_cmd = mini->command;
	while (curr_cmd)
	{
		if (has_exit_error(mini))
			break ;
		curr_cmd->argc = calc_argc(curr_cmd->argv);
		tmp = curr_cmd->argv;
		curr_cmd->argv = create_argv(mini, curr_cmd->argv, curr_cmd->argc);
		curr_cmd->argc = ft_doublesize((void **)curr_cmd->argv);
		create_redir(mini, tmp, &curr_cmd->redirect);
		ft_free_double((void ***)&tmp);
		if (is_builtin(curr_cmd->argv[0]) && !is_pipe(curr_cmd))
			mini->ret = exec_builtin_in_parent_proc(curr_cmd, mini);
		else
		{
			curr_cmd = exec_command_in_child_proc(curr_cmd, mini);
			mini->ret = wait_child_proc(mini);
		}
		curr_cmd = curr_cmd->next;
	}
}
