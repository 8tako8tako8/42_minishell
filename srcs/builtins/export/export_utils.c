#include "minishell.h"

int	is_onlyspace(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] != ' ')
		return (0);
	while (s[i])
	{
		if (s[i++] != ' ')
			return (0);
	}
	return (1);
}

static t_env	*lstdup(t_env *lst)
{
	t_env	*newlst;

	newlst = (t_env *)wrap_malloc(sizeof(t_env));
	newlst->key = strdup_safely((lst)->key);
	newlst->value = strdup_safely((lst)->value);
	newlst->next = NULL;
	return (newlst);
}

t_env	*dup_envlst(t_env *lst)
{
	t_env	*curr_lst;
	t_env	*newlst;
	t_env	*curr_newlst;

	if (!lst)
		return (NULL);
	curr_lst = lst;
	newlst = lstdup(curr_lst);
	curr_lst = curr_lst->next;
	curr_newlst = newlst;
	while (curr_lst != NULL)
	{
		curr_newlst->next = lstdup(curr_lst);
		curr_newlst = curr_newlst->next;
		curr_lst = curr_lst->next;
	}
	return (newlst);
}

void	put_key_and_value_in_export(char *key, char *value)
{
	char	*escaped;

	ft_putstr_fd("declare -x ", STDOUT);
	ft_putstr_fd(key, STDOUT);
	if (value == NULL)
		ft_putstr_fd("\n", STDOUT);
	else
	{
		escaped = escape_str(value);
		ft_putstr_fd("=\"", STDOUT);
		ft_putstr_fd(escaped, STDOUT);
		ft_putendl_fd("\"", STDOUT);
		free(escaped);
	}
}

t_env	*create_new_envlst_in_export(char *str)
{
	t_env	*new_env;
	char	*equal_ptr;

	new_env = (t_env *)wrap_malloc(sizeof(t_env));
	equal_ptr = ft_strchr(str, '=');
	if (equal_ptr == NULL)
	{
		new_env->key = strdup_safely(str);
		new_env->value = NULL;
		new_env->next = NULL;
	}
	else
	{
		if (*(equal_ptr - 1) == '+')
			new_env->key = substr_safely(str, 0, equal_ptr - str - 1);
		else
			new_env->key = substr_safely(str, 0, equal_ptr - str);
		new_env->value = ft_strtrim(equal_ptr + 1, " ");
		new_env->next = NULL;
	}
	return (new_env);
}
