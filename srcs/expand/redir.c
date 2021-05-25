#include "minishell.h"

static char	*alloc_ambiguous_redir(void)
{
	char	*s;

	s = wrap_malloc(sizeof(char) * 1);
	s[0] = -1;
	return (s);
}

char	*expand_redir_file(t_mini *mini, char *s)
{
	char	*tmp;
	char	*ret;
	char	**dummy;
	char	**lst;

	tmp = strdup_safely(s);
	dummy = (char **)wrap_malloc(sizeof(char *));
	*dummy = NULL;
	lst = expand_arg(mini, dummy, tmp);
	if (ft_doublesize((void **)lst) > 1 || *lst == NULL)
		ret = alloc_ambiguous_redir();
	else
		ret = strdup_safely(*lst);
	ft_free((void **)&tmp);
	ft_free_double((void ***)&lst);
	return (ret);
}
