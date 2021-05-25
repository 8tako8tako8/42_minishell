/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauehara <tauehara@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:13:28 by tauehara          #+#    #+#             */
/*   Updated: 2021/05/15 17:09:45 by tauehara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		assign_null(int ret_val, char **p)	//提出後修正(引数をchar * -> char **へ)
{
	if (p && *p)
		*p = NULL;
	return (ret_val);
}

int		mem_free(int ret_val, char **p1, char **p2)		//提出後修正(引数をchar * -> char **へ)
{
	if (p1 && *p1)
	{
		free(*p1);
		*p1 = NULL;
	}
	if (p2 && *p2)
	{
		free(*p2);
		*p2 = NULL;
	}
	return (ret_val);
}

int		read_oneline(int fd, char **line)
{
	char	*buf;
	int		read_size;
	char	*tmp;

	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (!(tmp = ft_strjoin(*line, buf)))
			return (mem_free(-1, &buf, NULL));
		free(*line);
		*line = tmp;
		if (BUFFER_SIZE > read_size && fd > 2 && !ft_strchr(*line, '\n'))
			return (mem_free(0, &buf, NULL));
		if (ft_strchr(*line, '\n'))
			return (mem_free(1, &buf, NULL));
	}
	if (read_size == -1)
		return (mem_free(-1, &buf, NULL));
	return (mem_free(0, &buf, NULL));
}

int		split_fst_nl(char **line, char **save)
{
	char *tmp;
	char *p_nl;

	if (!**line)
		return (0);
	if (!(p_nl = ft_strchr(*line, '\n')))
		return (1);
	*p_nl = '\0';
	if (!(tmp = ft_strdup(*line)))
		return (0);
	if (!(*save = ft_strdup(p_nl + 1)))
		return (mem_free(0, &tmp, NULL));
	free(*line);
	*line = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*save;
	int			is_reading;

	if (!line || fd < 0 || MAX_FD <= fd || BUFFER_SIZE <= 0)
		return (assign_null(-1, line));
	if (!save && !(save = ft_strdup("\0")))
		return (assign_null(-1, line));
	*line = save;
	save = NULL;
	is_reading = 1;
	if (!ft_strchr(*line, '\n') && (is_reading = read_oneline(fd, line)) == -1)
		return (mem_free(-1, line, NULL));
	if (!ft_strchr(*line, '\n') && !is_reading)
		return (0);
	if (!split_fst_nl(line, &save))
		return (mem_free(-1, line, &save));
	return (1);
}
