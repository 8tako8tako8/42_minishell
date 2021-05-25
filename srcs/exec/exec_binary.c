#include "minishell.h"

static void	error_handler_in_execve(char *path)
{
	if (is_directory(path))
	{
		put_error_binary(path, IS_A_DIRECTORY);
		exit(126);
	}
	if (errno == ENOENT)
	{
		put_error_binary(path, strerror(ENOENT));
		exit(127);
	}
	if (errno == ENOEXEC && (!is_executable(path) || !is_readable(path)))
		errno = EACCES;
	if (errno == ENOEXEC)
		exit(EXIT_SUCCESS);
	put_error_binary(path, strerror(errno));
	exit(126);
}

static int	get_lstsize_except_value_null(t_env *env)
{
	t_env	*curr_env;
	int		ret_i;

	if (!env)
		return (0);
	curr_env = env;
	ret_i = 0;
	while (curr_env != NULL)
	{
		if (curr_env->value != NULL)
			ret_i++;
		curr_env = curr_env->next;
	}
	return (ret_i);
}

static char	**create_env_char_array(t_env *env)
{
	char	**ret_environ;
	char	*tmp_environ;
	int		lstsize;
	int		i;

	lstsize = get_lstsize_except_value_null(env);
	ret_environ = (char **)wrap_malloc(sizeof(char *) * (lstsize + 1));
	i = 0;
	while (i < lstsize && env != NULL)
	{
		if (env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		tmp_environ = strjoin_safely(env->key, "=");
		ret_environ[i] = strjoin_safely(tmp_environ, env->value);
		free(tmp_environ);
		env = env->next;
		i++;
	}
	ret_environ[i] = NULL;
	return (ret_environ);
}

void	exec_binary(char **argv, t_env *env)
{
	char	**new_environ;
	char	*path;

	if (argv == NULL || argv[0] == NULL)
		exit(0);
	new_environ = create_env_char_array(env);
	if ((*argv)[0] == '/' || ft_strchr(argv[0], '/'))
		path = strdup_safely(argv[0]);
	else
		path = search_command(env, argv[0]);
	if ((execve(path, argv, new_environ)) < 0)
		error_handler_in_execve(path);
}
