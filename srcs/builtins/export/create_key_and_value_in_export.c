#include "minishell.h"

int	is_invalid_key(char *key)
{
	int		i;

	i = 1;
	while (key[i])
	{
		if (key[i] != '_' && !ft_isalpha(key[i]) && !ft_isdigit(key[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_underscore_or_alpha(char c)
{
	return (c == '_' || ft_isalpha(c));
}

static char	*create_key(char *str, int *plus_flag, char *equal_ptr)
{
	if (equal_ptr == NULL)
		return (strdup_safely(str));
	if (*(equal_ptr - 1) == '+')
	{
		*plus_flag = 1;
		return (substr_safely(str, 0, equal_ptr - str - 1));
	}
	return (substr_safely(str, 0, equal_ptr - str));
}

static char	*create_value(char *equal_ptr)
{
	char	*value;

	if (equal_ptr == NULL)
		return (NULL);
	value = strdup_safely(equal_ptr + 1);
	return (value);
}

int	create_key_and_value_in_export(
						char *str, int *plus_flag, char **key, char **value)
{
	char	*equal_ptr;

	if (!is_underscore_or_alpha(str[0]))
		return (INVALID_KEY);
	equal_ptr = ft_strchr(str, '=');
	*key = create_key(str, plus_flag, equal_ptr);
	if (is_invalid_key(*key))
	{
		free(*key);
		return (INVALID_KEY);
	}
	*value = create_value(equal_ptr);
	return (VALID_KEY);
}
