#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*curr_lst;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_lst = ft_lstlast(*lst);
	curr_lst->next = new;
}
