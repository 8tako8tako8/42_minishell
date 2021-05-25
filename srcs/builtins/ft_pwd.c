#include "minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	*directory;

	directory = mini->the_current_working_directory;
	if (!directory)
	{
		directory = get_working_directory(mini, "pwd");
		if (!directory)
			return (1);
	}
	ft_putendl_fd(directory, 1);
	if (directory != mini->the_current_working_directory)
		free(directory);
	return (0);
}
