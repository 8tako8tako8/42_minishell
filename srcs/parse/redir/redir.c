#include "minishell.h"

int	is_redir_op(char *s)
{
	return (ft_strchr_quote_escape(s, '>') || ft_strchr_quote_escape(s, '<'));
}

static int	get_redir_fd_io(char *lst, int type)
{
	if (ft_isdigit(*lst))
	{
		if (is_integer(1, lst))
			return (ft_atoi(lst));
		else
			return (-1);
	}
	if (type == TRUNC || type == APPEND)
		return (STDOUT);
	return (STDIN);
}

static int	get_redir_type(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_append(s, i))
			return (APPEND);
		else if (is_trunc(s, i))
			return (TRUNC);
		else if (is_input(s, i))
			return (INPUT);
		i++;
	}
	return (-1);
}

void	create_redir(t_mini *mini, char **lst, t_redirect **redir)
{
	int			type;
	int			fd_io;
	char		*filename;
	char		*tmp;
	int			li;

	li = 0;
	while (lst[li])
	{
		if (is_redir_op(lst[li]))
		{
			type = get_redir_type(lst[li]);
			fd_io = get_redir_fd_io(lst[li], type);
			filename = strdup_safely(lst[++li]);
			tmp = filename;
			filename = expand_redir_file(mini, filename);
			ft_rediradd_back(redir, ft_redirnew(fd_io, type, filename));
			(ft_redirlast(*redir))->before_expand = tmp;
		}
		li++;
	}
}
