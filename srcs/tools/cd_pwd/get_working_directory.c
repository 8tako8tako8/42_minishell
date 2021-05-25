#include "minishell.h"

char	*get_working_directory(t_mini *mini, const char *caller)
{
	if (!mini->the_current_working_directory)
	{
		mini->the_current_working_directory = getcwd(0, 0);
		if (!mini->the_current_working_directory)
		{
			put_error_get_working_directory((char *)caller);
			return (NULL);
		}
	}
	return (strdup_safely(mini->the_current_working_directory));
}
