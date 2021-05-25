#include "minishell.h"

static void	null_check_path(char *path, char *cmd)
{
	if (path == NULL)
	{
		put_error_binary(cmd, COMMAND_NOT_FOUND);
		exit(127);
	}
}

static char	*strjoin_path(char *path, char *slash, char *cmd)
{
	int		strlen;
	char	*tmp;
	char	*ret_path;

	strlen = ft_strlen(path);
	if (path[strlen - 1] != '/')
		tmp = strjoin_safely(path, slash);
	else
		tmp = strdup_safely(path);
	ret_path = strjoin_safely(tmp, cmd);
	free(tmp);
	return (ret_path);
}

static char	*search_command_in_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*ret_path;
	int		i;

	ret_path = NULL;
	i = 0;
	while (paths[i])
	{
		tmp = strjoin_path(paths[i], "/", cmd);
		if (check_command_in_path(tmp, &ret_path) && is_executable(tmp))
			break ;
		free(tmp);
		i++;
	}
	return (ret_path);
}

char	*search_command(t_env *env, char *cmd)
{
	char	*env_path;
	char	**paths;
	char	*ret_path;

	env_path = get_value_in_env(env, "PATH");
	if (env_path == NULL || *env_path == '\0')
	{
		ret_path = strdup_safely(cmd);
		return (ret_path);
	}
	paths = split_path(env_path);
	ret_path = search_command_in_paths(paths, cmd);
	null_check_path(ret_path, cmd);
	ft_free((void **)&paths);
	return (ret_path);
}
