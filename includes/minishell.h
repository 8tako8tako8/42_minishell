#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include "libft_ex.h"
# include "error.h"

# define STDIN				0
# define STDOUT				1
# define STDERR				2

# define SUCCESS			0
# define ERROR				1
# define IS_DIRECTORY		126
# define UNKNOWN_COMMAND	127
# define SYNTAX_ERROR		258

# define CMD				0
# define PIPE				1
# define END				2

# define INPUT				0
# define TRUNC				1
# define APPEND				2

# define PROMPT				"minishell$ "

# define SQUOTE				1
# define DQUOTE				2

# define BACK_SPACE			127
# define LEFT_ARROW			4479771
# define RIGHT_ARROW		4414235
# define UP_ARROW			4283163
# define DOWN_ARROW			4348699
# define CTRL_D				4
# define TAB_KEY			9
# define NEW_LINE			10
# define CONTINUE_INPUT		0
# define EXIT_SHELL			2
# define FINISH_INPUT		1
# define ONLY_NULL_CHAR		-1

# define STATUS_SUCCESS		0
# define STATUS_FAIL		1

# define VALID_REDIRECT		1
# define INVALID_REDIRECT	-1

# define REDIRECT_SUCCESS	1
# define REDIRECT_FAIL		-1

# define HISTORY_BACK		1
# define HISTORY_FORWARD	-1

# define USED_FD			1
# define UNUSED_FD			0

# define PARENT_PROC		1
# define CHILD_PROC			0

# define VALID_KEY			1
# define INVALID_KEY		-1

typedef struct s_history
{
	struct s_history	*prev;
	struct s_history	*next;
	char				*str;
	char				*tmp_current_str;
}						t_history;

typedef struct s_termcap
{
	char				*env;
	char				*bufptr;
	char				*move;
	char				*flush_char;
	char				*flush_line;
	char				*insert;
	char				*uninsert;
	int					row;
	int					col;
	int					row_size;
	int					col_size;
	int					prompt_size;
}						t_termcap;

typedef struct s_conon
{
	char				stub_char;
	char				*result;
	char				*p;
	char				*q;
	char				*base;
	char				*dotdot;
	int					rooted;
	int					double_slash_path;
	char				c;
}						t_canon;

typedef struct s_pipe
{
	int					is_pipe;
	int					is_prev_pipe;
	int					oldpipe[2];
	int					newpipe[2];
}						t_pipe;

typedef struct s_redirect
{
	struct s_redirect	*next;
	int					fd_io;
	int					type;
	char				*before_expand;
	char				*file;
	int					fd_open;
}						t_redirect;

typedef struct s_command
{
	struct s_command	*next;
	int					argc;
	char				**argv;
	int					op;
	pid_t				pid;
	t_redirect			*redirect;
}						t_command;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
}						t_token;

typedef struct s_node
{
	char				*str;
	int					type;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_mini
{
	t_env				*env;
	t_command			*command;
	char				*the_current_working_directory;
	t_history			*history;
	struct termios		oldterm;
	struct termios		term;
	t_termcap			tc;
	int					tmp_in;
	int					tmp_out;
	int					tmp_errout;
	int					*saved_fd;
	int					pid;
	int					sigint_flag;
	int					ret;
	int					exit_error;
}						t_mini;

/************/
/*   main   */
/************/
void		init_signal(t_mini *mini);
void		set_signal_handler_prompt(void);
void		set_signal_handler_no_prompt(void);

/************/
/*   term   */
/************/
void		init_termcap(t_mini *mini);
void		flush_line_after_cursor(t_termcap *tc);
void		flush_char(t_termcap *tc);
void		move_cursor_to_right_after_prompt(t_termcap *tc);
void		move_cursor_to_left_edge(t_termcap *tc, int lines);
void		move_cursor_to_dst(int col, int row, t_termcap *tc);
void		change_term_config(t_mini *mini);
void		reset_term_config(t_mini *mini);
void		set_insert_mode(t_termcap *tc);
void		unset_insert_mode(t_termcap *tc);
void		get_term_size(t_termcap *tc);
int			get_term_row_size(void);
int			get_term_col_size(void);
int			putchar_tc(int tc);

/**************/
/*   cursor   */
/**************/
void		get_cursor_position(t_termcap *tc);
int			get_cursor_row_position(void);
void		check_term_size(t_termcap *tc);
int			calc_num_of_lines(t_termcap *tc, int strlen);
void		calc_prompt_position_history(t_termcap *tc, int strlen);
void		calc_prompt_position_input(t_termcap *tc, t_history **history);
int			is_cursor_bottom_multiline(t_termcap *tc, int lines);
int			is_cursor_right_edge(t_termcap *tc);
int			is_multiline(t_termcap *tc, int strlen);

/*****************/
/*   read_line   */
/*****************/
char		*read_line(t_mini *mini);
int			divide_cases_by_key(int c, t_history **moved_hist, t_mini *mini);
int			delete_char(t_termcap *tc, t_history **history);
int			finish_command_reading(
				int c, t_termcap *tc, t_history **history, t_mini *mini);
int			add_char(int c, t_termcap *tc, t_history **history);
void		put_exit_and_exit_shell(t_termcap *tc, t_mini *mini);

/***************/
/*   history   */
/***************/
int			init_history(t_mini *mini);
t_history	*create_history(void);
void		add_front_new_history(t_history **history, t_history *new_history);
void		free_history(t_history *history);
int			get_history_size(t_history **history);
int			move_previous_history(
				t_termcap *tc, t_history **history, t_history **moved_hist);
int			move_next_history(
				t_termcap *tc, t_history **history, t_history **moved_hist);
void		flush_current_line(t_termcap *tc, int strlen);
char		*get_history_str(
				int key, t_history **history, t_history **moved_hist);

/*************/
/*   parse   */
/*************/
int			parse(t_mini *mini, char *cmd_line);
t_node		*ast_list(t_token **token);
t_node		*ast_pipeline(t_token **token);
t_node		*ast_command(t_token **token);
char		**create_argv(t_mini *mini, char **lst, int argc);
char		**expand_arg(t_mini *mini, char **argv, const char *str);
int			calc_argc(char **lst);
int			mark_env(char *s);

/**************/
/*   syntax   */
/**************/
char		*get_char_of_open_quotes_error(int quote_type);
int			validate_first_token(char *str);
int			validate_continuous_operator(char *str, int *ret);
int			validate_last_token(char *str);
int			validate_last_character(char *str);
int			set_error_type(int *ret, int errtype);
int			set_error_type_redir(int *ret, int errtype, char *str, int i);
int			set_error_type_inputs(int *ret, int errtype, char *str, int i);
int			get_fd(char *s, int i, int *ret);
int			is_redirection_op_continuous(char *str, int *i, char *prev_op);
int			is_control_op_continuous(
				char *str, int *i, char *prev_op, int *is_fd);
int			is_append_syntax(char *str, int *i);
void		reset_prev_op_and_is_redir_fd(char *prev_op, int *is_redir_fd);
int			is_ends_error(char *str, int i, char prev_op);
int			is_pipes_error(char *str, int i, char prev_op);
int			is_inputs_error(char *str, int i, char prev_op);
int			is_append_error(char *str, int i, char prev_op);

/*******************/
/*   parse/token   */
/*******************/
void		tokenize(t_token **token, char *p);
void		separate_token(
				t_token **token, char **str, char *sep, int sep_type);
t_token		*ft_newtoken(int type, char *str);
void		ft_tokenclear(t_token *token);
t_token		*ft_tokenlast(t_token *token);
void		ft_tokenadd_back(t_token **token, t_token *new);
int			consume_token(t_token **token, int type);

/******************/
/*   parse/node   */
/******************/
t_node		*ft_newnode(int type, char *str, t_node *left, t_node *right);
t_node		*ft_newnode_cmd(char *token);
void		ft_nodeclear(t_node *node);

/*********************/
/*   parse/command   */
/*********************/
void		create_command(t_mini *mini, t_node *node, t_command **command);
t_command	*ft_cmdnew(int argc, char **argv, int op, t_redirect *redirect);
t_command	*ft_cmdlast(t_command *cmd);
void		ft_cmdadd_back(t_command **cmd, t_command *new);
void		ft_cmdclear(t_command *cmd);

/*******************/
/*   parse/redir   */
/*******************/
void		create_redir(t_mini *mini, char **lst, t_redirect **redir);
int			is_redir_op(char *s);
t_redirect	*ft_redirnew(int fd_io, int type, char *file);
t_redirect	*ft_redirlast(t_redirect *redir);
void		ft_rediradd_back(t_redirect **redir, t_redirect *new);
void		ft_redirclear(t_redirect *redir);

/**************/
/*   expand   */
/**************/
char		*expand_environment(t_mini *mini, const char *s);
void		eliminate_unnecessary_space(char **p);
char		*expand_quote_escape(char *s);
char		*expand_redir_file(t_mini *mini, char *s);

/***********/
/*   env   */
/***********/
void		init_env(t_mini *mini);
t_env		*create_envlst(void);
void		delete_env(t_env **env, char *dstkey);
t_env		*create_new_envlst(const char *str);
void		bind_shlvl(t_env **env, int *shlvl_flag);
int			is_shlvl(char *environ);
void		add_envlst_back(t_env **env, t_env *new_env);
void		increment_shlvl(t_mini *mini);
char		*get_value_in_env(t_env *env, char *dstkey);
void		free_envlst(t_env *env);

/************/
/*   exec   */
/************/
void		exec_cmdlst(t_mini *mini);
int			exec_builtin_in_parent_proc(t_command *cmd, t_mini *mini);
t_command	*exec_command_in_child_proc(t_command *cmd, t_mini *mini);
void		init_pipe(t_pipe *pipe_struct);
int			is_pipe(t_command *cmd);
void		connect_pipes_stdin_stdout(t_pipe *pipe_info);
int			set_redirect(
				int is_parent_proc, t_redirect *redirect, t_mini *mini);
int			open_redirect_lst(t_redirect *redirect);
int			update_fd_io_by_redirect(
				int is_parent_proc, t_redirect *redirect, t_mini *mini);
void		exec_binary(char **argv, t_env *env);

/***********************/
/*   exec/exec_utils   */
/***********************/
int			check_redirect_filename(t_redirect *redir);
int			check_redirect_fd(t_redirect *redir);
int			is_invalid_fd(int fd);
char		*search_command(t_env *env, char *cmd);
char		**split_path(char *s);
char		**split_str(char **dst, char *s, int splitted_num);
int			is_directory(char *path);
int			is_readable(char *path);
int			is_executable(char *path);
int			check_command_in_path(char *path, char **ret_path);

/****************/
/*   builtins   */
/****************/
int			is_builtin(const char *arg);
int			exec_builtin(char **argv, t_mini *mini, int is_parent_proc);
int			ft_echo(char **argv);
int			ft_env(char **argv, t_env *env);
int			ft_unset(char **argv, t_env **env);
int			ft_pwd(t_mini *mini);

/***********************/
/*   builtins/export   */
/***********************/
int			ft_export(char **argv, t_mini *mini);
void		ft_export_without_args(t_env *env);
int			ft_export_with_args(char **argv, t_mini *mini);
int			is_invalid_key(char *key);
int			is_underscore_or_alpha(char c);
t_env		*dup_envlst(t_env *lst);
void		put_key_and_value_in_export(char *key, char *value);
t_env		*create_new_envlst_in_export(char *str);
char		*escape_str(char *value);
t_env		*lst_merge_sort(t_env *list);
int			create_key_and_value_in_export(
				char *str, int *plus_flag, char **key, char **value);
int			is_onlyspace(char *s);
void		update_env_value(int plus_flag, t_env *curr_env, char *value);
char		*strjoin_safely(char const *s1, char const *s2);

/******************/
/*   builtins/cd   */
/******************/
int			ft_cd(t_mini *mini, char **argv);
int			change_to_directory(t_mini *mini, char *newdir);
char		*make_absolute_path(const char *newdir, const char *currdir);
int			is_absolute_path(char *path);
char		*make_canonical_path(char *path);
int			is_doubleslash(char *path);
int			is_correct_directory(char *path);
int			is_dotslash_or_dotend(char *p);
int			is_dotdotslash_or_dotdotend(char *p);

/*********************/
/*   builtins/exit   */
/*********************/
int			ft_exit(char **argv, t_mini *mini, int is_parent_proc);
int			ft_atoi_in_exit(char *str, int is_parent_proc);
int			calc_exit_status(int arg);
int			is_number(char *str);

/*************/
/*   tools   */
/*************/
void		put_prompt(void);
void		*wrap_malloc(size_t size);
void		bind_env(t_mini *mini,
				const char *key, const char *value, int plus_flag);
t_env		*create_new_envlst_key_value(
				char const *key, const char *value);
char		*substr_safely(char const *s, unsigned int start, size_t len);
char		*strdup_safely(const char *str);
char		*strjoin_safely(char const *s1, char const *s2);
char		*charjoin_safely(const char *s, char c);
int			is_integer(int sign, char *nbr);
int			is_escaped(char *str, int i);

/********************/
/*   tools/cd_pwd   */
/********************/
void		set_working_directory(t_mini *mini, const char *name);
char		*get_working_directory(t_mini *mini, const char *caller);
void		set_pwd(t_mini *mini);
char		*reset_pwd(t_mini *mini, char *caller);
int			bind_pwd(t_mini *mini);

/**********************/
/*   tools/redir_op   */
/**********************/
int			calc_length_with_space_around_redir_op(char *s);
char		*strdup_with_space_around_redir_op(const char *s);
int			is_trunc(char *s, int i);
int			is_append(char *str, int i);
int			is_input(char *s, int i);

/*************/
/*   DEBUG   */
/*************/
void		put_tokens(t_token *token);
void		put_nodes(t_node *node);
void		put_cmds(t_command *cmd);

extern int				g_sigint;

#endif
