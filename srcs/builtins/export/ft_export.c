#include "minishell.h"

static void	free_key_value(char **key, char **value)
{
	free(*key);
	if (*value)
		free(*value);
}

int	ft_export_with_args(char **argv, t_mini *mini)
{
	int		i;
	char	*key;
	char	*value;
	int		plus_flag;
	int		ret_status;

	ret_status = 0;
	i = 0;
	while (argv[++i])
	{
		key = NULL;
		value = NULL;
		plus_flag = 0;
		if ((create_key_and_value_in_export(argv[i], &plus_flag, &key, &value))
			== INVALID_KEY)
		{
			put_error_builtin("export", NOT_A_VALID_IDENTIFIER, argv[i]);
			ret_status = STATUS_FAIL;
			continue ;
		}
		bind_env(mini, key, value, plus_flag);
		free_key_value(&key, &value);
	}
	return (ret_status);
}

void	ft_export_without_args(t_env *env)
{
	t_env	*dup_env;
	t_env	*sorted_env;
	t_env	*curr_env;

	dup_env = dup_envlst(env);
	sorted_env = lst_merge_sort(dup_env);
	curr_env = sorted_env;
	while (curr_env != NULL)
	{
		if (ft_strcmp(curr_env->key, "_") != 0)
			put_key_and_value_in_export(curr_env->key, curr_env->value);
		curr_env = curr_env->next;
	}
	free_envlst(sorted_env);
}

int	ft_export(char **argv, t_mini *mini)
{
	int		exit_status;

	exit_status = 0;
	if (argv[1] == NULL)
		ft_export_without_args(mini->env);
	else
		exit_status = ft_export_with_args(argv, mini);
	return (exit_status);
}
