/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_escape.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauehara <tauehara@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 23:13:17 by tauehara          #+#    #+#             */
/*   Updated: 2021/05/14 01:32:18 by tauehara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**mem_free(char **words, int words_i)
{
	int	i;

	i = 0;
	while (i < words_i)
		free(words[i]);
	free(words);
	return (NULL);
}

static void	check_prev_bs(int *is_prev_bs, char *s, int i)
{
	if (!*is_prev_bs && s[i] == '\\')
		*is_prev_bs = 1;
	else
		*is_prev_bs = 0;
}

static int	calc_words_cnt(char *s, char c)
{
	int	word_len;
	int	words_cnt;
	int	i;
	int	is_prev_bs;

	word_len = 0;
	words_cnt = 0;
	is_prev_bs = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && ft_isquoting(s, i) == 0 && !is_prev_bs)
			word_len = 0;
		else
		{
			if (word_len == 0)
				words_cnt++;
			word_len++;
			check_prev_bs(&is_prev_bs, s, i);
		}
		i++;
	}
	return (words_cnt);
}

static char	**split_words(char **words, int words_cnt, char *s, char c)
{
	int	n[4];

	ft_bzero(n, sizeof(int) * 4);
	while (n[1] < words_cnt)
	{
		if (!s[n[2]] || (s[n[2]] == c && ft_isquoting(s, n[2]) == 0 && !n[3]))
		{
			if (n[0])
			{
				words[n[1]] = ft_substr(s + (n[2] - n[0]), 0, n[0]);
				if (!(words[n[1]++]))
					return (mem_free(words, n[1]));
			}
			n[0] = 0;
		}
		else
		{
			n[0]++;
			check_prev_bs(n + 3, s, n[2]);
		}
		n[2]++;
	}
	words[n[1]] = NULL;
	return (words);
}

char	**ft_split_quote_escape(char const *s, char c)
{
	int		words_cnt;
	char	**words;
	char	sep[2];

	if (!s)
		return (NULL);
	words_cnt = calc_words_cnt((char *)s, c);
	words = (char **)malloc((words_cnt + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	if (words_cnt == 1)
	{
		sep[0] = c;
		sep[1] = '\0';
		words[0] = ft_strtrim(s, sep);
		if (!words[0])
			return (mem_free(words, words_cnt));
		words[1] = NULL;
		return (words);
	}
	words = split_words(words, words_cnt, (char *)s, c);
	if (!words)
		return (NULL);
	return (words);
}
