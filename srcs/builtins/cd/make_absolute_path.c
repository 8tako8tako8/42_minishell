#include "minishell.h"

int	is_absolute_path(char *path)
{
	return ((path && *path == '/'));
}

static char	*make_path(const char *currdir, const char *newdir)
{
	char	*ret;
	char	*path;
	char	*r;
	char	*s;

	if (!currdir || !*currdir)
		path = strdup_safely(".");
	else
		path = (char *)currdir;
	ret = (char *)wrap_malloc(2 + ft_strlen(path) + ft_strlen(newdir));
	r = ret;
	s = path;
	while (*s)
		*r++ = *s++;
	if (s[-1] != '/')
		*r++ = '/';
	s = (char *)newdir;
	while (*s)
		*r++ = *s++;
	*r = '\0';
	if (path != currdir)
		ft_free((void **)&path);
	return (ret);
}

char	*make_absolute_path(const char *newdir, const char *currdir)
{
	if (currdir == NULL || is_absolute_path((char *)newdir))
		return (strdup_safely((char *)newdir));
	return (make_path(currdir, newdir));
}
