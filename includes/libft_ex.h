#ifndef LIBFT_EX_H
# define LIBFT_EX_H

# include "libft.h"

//もういらない？
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif

# define MAX_FD			10000

int		ft_strcmp(const char *s1, const char *s2);
void	ft_strncpy(char *dst, char *src, size_t n);
int		get_next_line(int fd, char **line);
int		ft_isquoting(const char *str, int n);
char	*ft_strchr_quote_escape(char *str, char c);
char	**ft_split_quote_escape(char const *s, char c);
char	*ft_charjoin(const char *s, char c);

void	ft_free(void **p);
void	ft_free_double(void ***p);

void	*ft_doublelast(void	**p);
size_t	ft_doublesize(void **p);
void	**ft_doubledup(void	**p);
void	**ft_doublecat(void	**dst, void **src);
void	**ft_doublejoin(void **p1, void **p2);
void	**ft_doubleadd_back(void	**p, void *new);
void	**ft_doublemap(void **old, char *(*f)(char *));
int		ft_is_quotedstr(char *s, int quote_type);

#endif
