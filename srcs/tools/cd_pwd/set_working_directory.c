#include "minishell.h"

void	set_working_directory(t_mini *mini, const char *name)
{
	ft_free((void **)&mini->the_current_working_directory);
	mini->the_current_working_directory = strdup_safely((char *)name);
}
