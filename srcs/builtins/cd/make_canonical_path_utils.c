#include "minishell.h"

int	is_doubleslash(char *path)
{
	return ((path[0] == '/' && path[1] == '/' && (path[2] != '/')));
}

int	is_correct_directory(char *path)
{
	struct stat	sb;

	errno = 0;
	return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}

int	is_dotslash_or_dotend(char *p)
{
	return (p[0] == '.' && (p[1] == '/' || p[1] == '\0'));
}

int	is_dotdotslash_or_dotdotend(char *p)
{
	return (p[0] == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0'));
}
