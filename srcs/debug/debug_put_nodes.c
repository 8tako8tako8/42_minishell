#include "minishell.h"

void	put_nodes(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		put_nodes(node->left);

	printf("====================\n");

	printf(" type : ");
	if (node->type == END)
		printf("END\n");
	else if (node->type == PIPE)
		printf("PIPE\n");
	else if (node->type == CMD)
		printf("CMD\n");

	printf(" str  : %s\n", node->str);

	if (node->right)
		put_nodes(node->right);
}
