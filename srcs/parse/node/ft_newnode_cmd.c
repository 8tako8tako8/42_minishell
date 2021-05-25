#include "minishell.h"

t_node	*ft_newnode_cmd(char *token)
{
	t_node	*node;

	node = (t_node *)wrap_malloc(sizeof(t_node));
	node->type = CMD;
	node->str = strdup_safely(token);
	node->left = NULL;
	node->right = NULL;
	return (node);
}
