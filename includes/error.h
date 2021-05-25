#ifndef ERROR_H
# define ERROR_H

# include "libft.h"

# define STDIN							0
# define STDOUT							1
# define STDERR							2

# define VALID							1
# define INVALID						0

# define ERR_FD_OVERFLOW				-1
# define ERR_END						-2
# define ERR_ENDS						-3
# define ERR_PIPE						-4
# define ERR_PIPES						-5
# define ERR_NEWLINE					-6
# define ERR_INPUT						-7
# define ERR_TRUNC						-8
# define ERR_INPUTS						-9
# define ERR_APPEND						-10

# define PIPE_STR						"|"
# define PIPES_STR						"||"
# define END_STR						";"
# define ENDS_STR						";;"
# define TRUNC_STR						">"
# define APPEND_STR						">>"	
# define INPUT_STR						"<"
# define INPUTS_STR						"<<"
# define NEWLINE_STR					"newline"
# define FD_OVERFLOW_STR				"-1"

# define SQUOTE_STR						"\'"
# define DQUOTE_STR						"\""

# define OPEN_QUOTES					"unexpected EOF while looking for \
matching"
# define UNEXPECTED_TOKEN				"syntax error near unexpected token"
# define BAD_FD							"Bad file descriptor"
# define FD_OUT_OF_RANGE				"file descriptor out of range"

# define SHLVL_TOO_HIGH                 "minishell: warning: shell level \
(1001) too high, resetting to 1"

# define NO_SUCH_FILE				    "No such file or directory"
# define AMBIGUOUS_REDIRECT				"ambiguous redirect"
# define BAD_FILE_DESCRIPTOR			"Bad file descriptor"

# define COMMAND_NOT_FOUND				"command not found"
# define IS_A_DIRECTORY					"is a directory"

# define NOT_A_VALID_IDENTIFIER			"not a valid identifier"
# define OPTIONS_ARE_NOT_SUPPORTED		"options are not supported"
# define ARGUMENTS_ARE_NOT_SUPPORTED	"arguments are not supported"

# define TOO_MANY_ARGUMENTS				"too many arguments"
# define NUMERIC_ARGUMENT_REQUIRED		"numeric argument required"

int		put_error(char *err_str, char *target);
int		put_error_unexpected_token(int nbr);
void	put_error_unexpected_token_fd(int nbr);
int		put_error_fd(int fd);
void	put_error_and_exit(void);
int		put_error_builtin(char *cmd, char *err_str, char *target);
int		put_error_binary(char *cmd, char *err_str);
int		put_error_cd(char *dirname);
int		put_error_get_working_directory(char *caller);
int		put_error_open(char *file);
int		put_error_redirect(char *file, int fd, char *str);
int		put_error_exit(char *cmd, char *err_str, char *arg, int is_parent_proc);

#endif
