#include "minishell.h"

int	consume_token(t_token **token, int type)
{
	if (token && *token && (*token)->type == type)
	{
		*token = (*token)->next;
		return (1);
	}
	return (0);
}

void	separate_token(t_token **token, char **cmd_line, char *sep,
																int sep_type)
{
	char	sep_char[2];
	char	*s;

	sep_char[0] = *sep;
	sep_char[1] = '\0';
	*sep = '\0';
	if (*cmd_line < sep)
	{
		s = strdup_safely(*cmd_line);
		ft_tokenadd_back(token, ft_newtoken(CMD, s));
	}
	s = strdup_safely(sep_char);
	ft_tokenadd_back(token, ft_newtoken(sep_type, s));
	*cmd_line = sep + 1;
}

void	tokenize(t_token **token, char *cmd_line)
{
	char	*end;
	char	*pipe;
	char	*cmd;

	while (*cmd_line)
	{
		end = ft_strchr_quote_escape(cmd_line, ';');
		pipe = ft_strchr_quote_escape(cmd_line, '|');
		if (end && (!pipe || end < pipe))
			separate_token(token, &cmd_line, end, END);
		else if (pipe)
			separate_token(token, &cmd_line, pipe, PIPE);
		else
		{
			cmd = strdup_safely(cmd_line);
			ft_tokenadd_back(token, ft_newtoken(CMD, cmd));
			break ;
		}
	}
}
