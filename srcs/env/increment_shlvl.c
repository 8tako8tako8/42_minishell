#include "minishell.h"

static int	ft_atoi_in_shlvl(const char *str)
{
	long long		number;
	int				sign;
	int				i;

	number = 0;
	sign = 1;
	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (is_integer(sign, (char *)str + i) == 0)
		return (0);
	while (ft_isdigit(str[i]))
	{
		number = number * 10;
		number += str[i++] - '0';
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (0);
	return (number * sign);
}

void	increment_shlvl(t_mini *mini)
{
	char	*tmp;
	int		shlvl;
	char	*new_shlvl;

	tmp = get_value_in_env(mini->env, "SHLVL");
	shlvl = ft_atoi_in_shlvl(tmp);
	free(tmp);
	if (0 <= shlvl && shlvl < 999)
	{
		new_shlvl = ft_itoa(shlvl + 1);
		bind_env(mini, "SHLVL", new_shlvl, 0);
		free(new_shlvl);
		return ;
	}
	if (shlvl == 999)
		bind_env(mini, "SHLVL", "", 0);
	else if (shlvl > 999)
	{
		ft_putendl_fd(SHLVL_TOO_HIGH, STDERR);
		bind_env(mini, "SHLVL", "1", 0);
	}
	else if (shlvl < 0)
		bind_env(mini, "SHLVL", "0", 0);
}
