#include "minishell.h"

static void	set_stubchar_base_doubleslashpath(t_canon *cn)
{
	if (cn->rooted)
	{
		cn->stub_char = '/';
		cn->base = cn->result + 1;
		cn->double_slash_path = is_doubleslash(cn->result);
		cn->base += cn->double_slash_path;
		return ;
	}
	cn->stub_char = '.';
	cn->base = cn->result;
	cn->double_slash_path = 0;
}

int	dotdotslash_or_dotdotend(t_canon *cn)
{
	cn->p += 2;
	if (cn->q > cn->dotdot)
	{
		cn->c = *cn->q;
		*cn->q = '\0';
		if (is_correct_directory(cn->result) == 0)
		{
			free(cn->result);
			return (0);
		}
		*cn->q = cn->c;
		while (--cn->q > cn->dotdot && *cn->q != '/')
			;
	}
	else if (cn->rooted == 0)
	{
		if (cn->q != cn->base)
			*cn->q++ = '/';
		*cn->q++ = '.';
		*cn->q++ = '.';
		cn->dotdot = cn->q;
	}
	return (1);
}

int	canon_dir(t_canon *cn)
{
	if (cn->q != cn->base)
		*cn->q++ = '/';
	while (*cn->p && (*cn->p != '/'))
		*cn->q++ = *cn->p++;
	cn->c = *cn->q;
	*cn->q = '\0';
	if (is_correct_directory(cn->result) == 0)
	{
		free(cn->result);
		return (0);
	}
	*cn->q = cn->c;
	return (1);
}

int	canon_path(t_canon *cn)
{
	cn->p = cn->base;
	cn->q = cn->base;
	cn->dotdot = cn->base;
	while (*cn->p)
	{
		if (cn->p[0] == '/')
			cn->p++;
		else if (is_dotslash_or_dotend(cn->p))
			cn->p++;
		else if (is_dotdotslash_or_dotdotend(cn->p))
		{
			if (dotdotslash_or_dotdotend(cn) == 0)
				return (0);
		}
		else
		{
			if (canon_dir(cn) == 0)
				return (0);
		}
	}
	return (1);
}

char	*make_canonical_path(char *path)
{
	t_canon	cn;

	cn.result = strdup_safely(path);
	cn.rooted = is_absolute_path(path);
	set_stubchar_base_doubleslashpath(&cn);
	if (canon_path(&cn) == 0)
		return (NULL);
	if (cn.q == cn.result)
		*cn.q++ = cn.stub_char;
	*cn.q = '\0';
	if (is_doubleslash(cn.result) && cn.double_slash_path == 0)
	{
		if (cn.result[2] == '\0')
			cn.result[1] = '\0';
		else
			ft_memmove(cn.result, cn.result + 1, ft_strlen(cn.result));
	}
	return (cn.result);
}
