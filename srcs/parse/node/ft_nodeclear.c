#include "minishell.h"

void	ft_nodeclear(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		ft_nodeclear(node->left);
	if (node->right)
		ft_nodeclear(node->right);
	free(node->str);
	free(node);
}
