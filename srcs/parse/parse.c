#include "minishell.h"

static int	validate_syntax(char *cmd)
{
	int	ret;

	ret = 1;
	if (ft_isquoting(cmd, INT_MAX))
		return (put_error(OPEN_QUOTES,
				get_char_of_open_quotes_error(ft_isquoting(cmd, INT_MAX))));
	ret = validate_first_token(cmd);
	if (ret < 0)
		return (put_error_unexpected_token(ret));
	if (!validate_continuous_operator(cmd, &ret))
		return (put_error_unexpected_token(ret));
	ret = validate_last_token(cmd);
	if (ret < 0)
		return (put_error_unexpected_token(ret));
	ret = validate_last_character(cmd);
	if (ret < 0)
		return (put_error_unexpected_token(ret));
	return (VALID);
}

int	parse(t_mini *mini, char *cmd_line)
{
	t_token		*token;
	t_token		*tmp_token;
	t_node		*node;

	if (ft_strlen(cmd_line) == 0)
		return (0);
	if (!validate_syntax(cmd_line))
	{
		mini->ret = SYNTAX_ERROR;
		return (0);
	}
	token = NULL;
	tokenize(&token, cmd_line);
	tmp_token = token;
	node = ast_list(&token);
	ft_tokenclear(tmp_token);
	mini->command = NULL;
	create_command(mini, node, &mini->command);
	ft_nodeclear(node);
	return (1);
}
