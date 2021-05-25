#include "minishell.h"

int	is_directory(char *path)
{
	struct stat		st;

	return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

int	is_readable(char *path)
{
	struct stat		st;

	return (stat(path, &st) == 0 && (st.st_mode & S_IRUSR) == S_IRUSR);
}

int	is_executable(char *path)
{
	struct stat		st;

	return (stat(path, &st) == 0 && (st.st_mode & S_IXUSR) == S_IXUSR);
}

int	check_command_in_path(char *path, char **ret_path)
{
	struct stat		st;

	if (lstat(path, &st) == -1)
		return (0);
	if (is_directory(path))
		return (0);
	free(*ret_path);
	*ret_path = strdup_safely(path);
	return (1);
}
