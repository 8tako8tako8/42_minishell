#include "minishell.h"

static void	assign_operator_type(t_node *node, t_command **command)
{
	if (node->type == END)
		ft_cmdlast(*command)->op = 0;
	else if (node->type == PIPE)
		ft_cmdlast(*command)->op = 1;
}

static void	parse_command(
		t_mini *mini, t_node *node, t_command **command, char **lst)
{
	char		*str;
	char		**argv;

	(void)mini;
	str = strdup_with_space_around_redir_op(node->str);
	lst = ft_split_quote_escape(str, ' ');
	if (!lst)
		put_error_and_exit();
	ft_free((void **)&str);
	argv = lst;
	ft_cmdadd_back(command, ft_cmdnew(-1, argv, 0, NULL));
}

void	create_command(t_mini *mini, t_node *node, t_command **command)
{
	char	**lst;

	lst = NULL;
	if (node->left)
		create_command(mini, node->left, command);
	if (node->type == CMD)
		parse_command(mini, node, command, lst);
	else
		assign_operator_type(node, command);
	if (node->right)
		create_command(mini, node->right, command);
}
