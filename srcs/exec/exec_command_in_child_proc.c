#include "minishell.h"

static void	update_pipe_in_parent_proc(t_pipe *pipe_info)
{
	if (pipe_info->is_prev_pipe)
	{
		close(pipe_info->oldpipe[0]);
		close(pipe_info->oldpipe[1]);
	}
	if (pipe_info->is_pipe)
	{
		pipe_info->oldpipe[0] = pipe_info->newpipe[0];
		pipe_info->oldpipe[1] = pipe_info->newpipe[1];
	}
}

static void	exec_command(char *argv[], t_pipe *pipe_info,
	t_redirect *redirect, t_mini *mini)
{
	int		exit_status;

	if (pipe_info->is_pipe)
		pipe(pipe_info->newpipe);
	set_signal_handler_no_prompt();
	mini->pid = fork();
	if (mini->pid < 0)
		put_error_and_exit();
	if (mini->pid == 0)
	{
		connect_pipes_stdin_stdout(pipe_info);
		if (set_redirect(CHILD_PROC, redirect, mini) == REDIRECT_FAIL)
			exit(STATUS_FAIL);
		if (is_builtin(argv[0]))
		{
			exit_status = exec_builtin(argv, mini, CHILD_PROC);
			exit(exit_status);
		}
		else
			exec_binary(argv, mini->env);
	}
	update_pipe_in_parent_proc(pipe_info);
}

t_command	*exec_command_in_child_proc(t_command *cmd, t_mini *mini)
{
	t_pipe	pipe_info;
	char	**tmp;

	init_pipe(&pipe_info);
	while (cmd)
	{
		pipe_info.is_pipe = is_pipe(cmd);
		exec_command(cmd->argv, &pipe_info, cmd->redirect, mini);
		pipe_info.is_prev_pipe = is_pipe(cmd);
		if (pipe_info.is_prev_pipe)
		{
			cmd = cmd->next;
			cmd->argc = calc_argc(cmd->argv);
			tmp = cmd->argv;
			cmd->argv = create_argv(mini, cmd->argv, cmd->argc);
			cmd->argc = ft_doublesize((void **)cmd->argv);
			create_redir(mini, tmp, &cmd->redirect);
			ft_free_double((void ***)&tmp);
		}
		else
			break ;
	}
	return (cmd);
}
