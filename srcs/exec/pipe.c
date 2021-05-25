#include "minishell.h"

void	init_pipe(t_pipe *pipe_info)
{
	pipe_info->is_prev_pipe = 0;
	pipe_info->oldpipe[0] = -1;
	pipe_info->oldpipe[1] = -1;
}

int	is_pipe(t_command *cmd)
{
	return (cmd->op == 1);
}

static void	connect_stdin_to_prev_command(t_pipe *pipe_info)
{
	close(pipe_info->oldpipe[1]);
	dup2(pipe_info->oldpipe[0], STDIN);
	close(pipe_info->oldpipe[0]);
}

static void	connect_stdout_to_next_command(t_pipe *pipe_info)
{
	close(pipe_info->newpipe[0]);
	dup2(pipe_info->newpipe[1], STDOUT);
	close(pipe_info->newpipe[1]);
}

void	connect_pipes_stdin_stdout(t_pipe *pipe_info)
{
	if (pipe_info->is_prev_pipe)
		connect_stdin_to_prev_command(pipe_info);
	if (pipe_info->is_pipe)
		connect_stdout_to_next_command(pipe_info);
}
