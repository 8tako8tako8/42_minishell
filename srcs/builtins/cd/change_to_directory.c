#include "minishell.h"

static void	reset_the_current_working_directory(t_mini *mini)
{
	char	*tmp;

	tmp = get_working_directory(mini, "chdir");
	if (tmp)
		ft_free((void **)&tmp);
}

static void	check_canon_failed_and_set_t_tdir(
									int *canon_failed, char **t, char **tdir)
{
	if (*tdir && **tdir)
	{
		ft_free((void **)t);
		return ;
	}
	if (*tdir)
		ft_free((void **)tdir);
	*tdir = *t;
	*canon_failed = 1;
}

static int	chdir_abspath(t_mini *mini, char *t, char *tdir, int canon_failed)
{
	if (chdir(tdir) == 0)
	{
		if (canon_failed)
		{
			t = reset_pwd(mini, "cd");
			if (t == NULL)
				set_working_directory(mini, tdir);
		}
		else
			set_working_directory(mini, tdir);
		ft_free((void **)&tdir);
		return (1);
	}
	return (0);
}

static int	chdir_newdir(t_mini *mini, char *newdir, char *t, char *tdir)
{
	int	r;
	int	err;

	err = errno;
	if (chdir(newdir) == 0)
	{
		t = reset_pwd(mini, "cd");
		if (!t)
			set_working_directory(mini, tdir);
		else
			ft_free((void **)&t);
		r = 1;
	}
	else
	{
		errno = err;
		r = 0;
	}
	ft_free((void **)&tdir);
	return (r);
}

int	change_to_directory(t_mini *mini, char *newdir)
{
	char	*t;
	char	*tdir;
	int		canon_failed;

	tdir = NULL;
	if (mini->the_current_working_directory == NULL)
		reset_the_current_working_directory(mini);
	t = make_absolute_path(newdir, mini->the_current_working_directory);
	tdir = make_canonical_path(t);
	canon_failed = 0;
	check_canon_failed_and_set_t_tdir(&canon_failed, &t, &tdir);
	if (chdir_abspath(mini, t, tdir, canon_failed))
		return (1);
	return (chdir_newdir(mini, newdir, t, tdir));
}
