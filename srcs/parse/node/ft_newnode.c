#include "minishell.h"

t_node	*ft_newnode(int type, char *token, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)wrap_malloc(sizeof(t_node));
	node->type = type;
	node->str = token;
	node->left = left;
	node->right = right;
	return (node);
}
