#include "minishell.h"

char	*reset_pwd(t_mini *mini, char *caller)
{
	char	*tdir;

	if (mini->the_current_working_directory)
		free(mini->the_current_working_directory);
	mini->the_current_working_directory = NULL;
	tdir = get_working_directory(mini, caller);
	return (tdir);
}
