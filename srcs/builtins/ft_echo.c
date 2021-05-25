#include "minishell.h"

static int	is_n_option(char *str, int *n_option)
{
	int		i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (ft_strlen(str) >= 2 && str[i] == '\0')
	{
		*n_option = 1;
		return (1);
	}
	return (0);
}

int	ft_echo(char **argv)
{
	int		n_option;
	int		i;

	n_option = 0;
	i = 1;
	while (argv[i] && is_n_option(argv[i], &n_option))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT);
		if (argv[i + 1])
			write(1, " ", STDOUT);
		i++;
	}
	if (n_option == 0)
		write(STDOUT, "\n", 1);
	return (STATUS_SUCCESS);
}
