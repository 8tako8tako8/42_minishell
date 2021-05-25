#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr_lst;
	int		i;

	if (lst == NULL)
		return (0);
	curr_lst = lst;
	i = 1;
	while (curr_lst->next != NULL)
	{
		curr_lst = curr_lst->next;
		i++;
	}
	return (i);
}
