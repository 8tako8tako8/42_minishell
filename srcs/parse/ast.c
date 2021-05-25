#include "minishell.h"

t_node	*ast_command(t_token **token)
{
	t_node	*node;

	if (!token || !*token)
		return (NULL);
	node = ft_newnode(CMD, strdup_safely((*token)->str), NULL, NULL);
	consume_token(token, CMD);
	return (node);
}

t_node	*ast_pipeline(t_token **token)
{
	t_node	*node;

	node = ast_command(token);
	while (1)
	{
		if (consume_token(token, PIPE))
			node = ft_newnode(
					PIPE, strdup_safely("|"), node, ast_command(token));
		else
			return (node);
	}
}

t_node	*ast_list(t_token **token)
{
	t_node	*node;

	node = ast_pipeline(token);
	while (1)
	{
		if (consume_token(token, END))
			node = ft_newnode(
					END, strdup_safely(";"), node, ast_pipeline(token));
		else
			return (node);
	}
}
