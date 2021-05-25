#include "minishell.h"

int	calc_exit_status(int arg)
{
	int		ret_status;

	if (arg > 255)
		ret_status = arg % 256;
	else if (arg < 0)
		ret_status = 256 + (arg % 256);
	else
		ret_status = arg;
	return (ret_status);
}

int	is_number(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int	check_long_overflow(int sign, const char *str)
{
	int		digit;

	digit = 0;
	while (ft_isdigit(str[digit]))
		digit++;
	if ((sign == -1 && digit > 19))
		return (-1);
	if ((sign == 1 && digit > 19))
		return (-1);
	if ((sign == 1 && ft_strncmp(str, "9223372036854775807", 19) > 0)
		&& digit == 19)
		return (-1);
	if ((sign == -1 && ft_strncmp(str, "9223372036854775808", 19) > 0)
		&& digit == 19)
		return (-1);
	return (1);
}

int	ft_atoi_in_exit(char *str, int is_parent_proc)
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
	if (check_long_overflow(sign, str + i) == -1)
	{
		put_error_exit("exit", NUMERIC_ARGUMENT_REQUIRED, str, is_parent_proc);
		exit(255);
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10;
		number += str[i] - '0';
		i++;
	}
	return (number * sign);
}
