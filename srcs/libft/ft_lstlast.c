#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr_list;

	if (lst == NULL)
		return (NULL);
	curr_list = lst;
	while (curr_list->next != NULL)
		curr_list = curr_list->next;
	return (curr_list);
}
