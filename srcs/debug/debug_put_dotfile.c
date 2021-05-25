#include "minishell.h"

void	put_number(int i, int fd)
{
	ft_putstr_fd("(", fd);
	ft_putstr_fd(ft_itoa(i), fd); 
	ft_putstr_fd(")", fd);
}

void	put_node(char *str, int fd, int i)
{
	ft_putstr_fd("\"", fd);
	put_number(i, fd);
	if (!ft_strcmp(str, ";"))
		ft_putstr_fd("SEMI", fd);
	else if (!ft_strcmp(str, "|"))
		ft_putstr_fd("PIPE", fd);
	else
		ft_putstr_fd(str, fd);
	ft_putstr_fd("\"", fd);
}

void	put_relation(char *left, char *right, int fd, int i)
{
	ft_putstr_fd("\t", fd);
	put_node(left, fd, i);
	ft_putstr_fd("->", fd);
	put_node(right, fd, i + 1);
	ft_putstr_fd(";\n", fd);
}

void	put_dotfile_node(t_node *node, int fd, int i)
{
	i++;
	
	if (node->left)
		put_relation(node->str, node->left->str, fd, i);

	if (node->right)
		put_relation(node->str, node->right->str, fd, i);

	if (node->left)
		put_dotfile_node(node->left, fd, i);

	if (node->right)
		put_dotfile_node(node->right, fd, i);
}

//void	put_dotfile(t_node *node)
//{
//	int fd;
//
//	fd = open("node.dot", O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
//	ft_putstr_fd("digraph graph_name {\n", fd);
//	
//	put_dotfile_node(node, fd, 0);
//
//	ft_putstr_fd("}", fd);
//
//	close(fd);
//}
