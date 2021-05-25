CC			:=	gcc
CFLAGS		:=	-g -Wall -Wextra -Werror
NAME		:=	minishell
SRC_DIR		:=	./srcs
FT_DIR		:=	$(SRC_DIR)/libft
FT_LIB		:=	ft
LIBS		:=	-L$(FT_DIR) -l$(FT_LIB) -lncurses
INCLUDE 	:=  -I$(FT_DIR) -I./includes


MAIN		:=	main signal

PARSE		:=	parse ast arg

SYNTAX		:=	first_token continuous_operator continuous_operator_utils continuous_operator_utils2 continuous_operator_utils3 last_token last_character open_quotes

TOKEN		:=	tokenize ft_newtoken ft_tokenclear ft_tokenlast ft_tokenadd_back

NODE		:=	ft_newnode ft_newnode_cmd ft_nodeclear

COMMAND		:=	command ft_cmdnew ft_cmdlast ft_cmdadd_back ft_cmdclear

REDIR		:=	redir ft_redirnew ft_redirlast ft_rediradd_back ft_redirclear

ENV			:=	init_env create_envlst create_envlst_utils free_envlst add_envlst_back increment_shlvl get_value_in_env update_env_value delete_env

EXPAND		:=	env redir quote_escape

BUILTINS	:=	builtin ft_echo ft_env ft_unset ft_pwd

CD			:=	ft_cd change_to_directory make_absolute_path make_canonical_path make_canonical_path_utils

EXPORT		:=	ft_export export_utils create_key_and_value_in_export escape_str

EXIT		:=	ft_exit exit_utils

EXEC		:=	exec_cmdlst exec_builtin_in_parent_proc exec_command_in_child_proc pipe set_redirect open_redirect_lst update_redirect exec_binary

EXEC_UTILS	:=	search_command split_path split_path_utils check_stat check_redirect

TOOLS		:=	prompt is_integer lst_merge_sort wrap_malloc is_escaped strjoin_safely substr_safely strdup_safely bind_env charjoin_safely

CD_PWD		:=	set_pwd	reset_pwd get_working_directory set_working_directory bind_pwd

REDIR_OP	:=	strdup_with_space_around_redir_op calc_length_with_space_around_redir_op is_trunc is_append is_input

ERROR		:=	error cd exit builtin syntax redirect

DEBUG		:=	debug_put_tokens debug_put_nodes debug_put_dotfile debug_put_cmds

READ_LINE	:=	add_char delete_char divide_cases_by_key finish_command_reading read_line put_exit_and_exit_shell

HISTORY		:=	history move_history flush_current_line get_history_str

TERM		:=	init_termcap term_config get_term_size termcap_insert termcap_delete termcap_move putchar_tc

CURSOR		:=	get_cursor_position check_term_size calc_prompt_position is_multiline is_cursor_right_edge

LIBFT_EX	:=	ft_strcmp ft_isquoting ft_strchr_quote_escape ft_split_quote_escape ft_charjoin ft_strncpy ft_free ft_free_double ft_doublesize ft_doublelast ft_doubledup ft_doublecat ft_doublejoin ft_doubleadd_back  ft_doublemap ft_is_quotedstr get_next_line get_next_line_utils

SRCS		:=	$(addsuffix .c, $(addprefix $(SRC_DIR)/main/, $(MAIN))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/libft_ex/, $(LIBFT_EX))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/parse/, $(PARSE))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/parse/token/, $(TOKEN))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/parse/node/, $(NODE))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/parse/command/, $(COMMAND))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/parse/redir/, $(REDIR))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/syntax/, $(SYNTAX))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/env/, $(ENV))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/expand/, $(EXPAND))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/builtins/, $(BUILTINS))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/builtins/cd/, $(CD))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/builtins/export/, $(EXPORT))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/builtins/exit/, $(EXIT))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/exec/, $(EXEC))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/exec/exec_utils/, $(EXEC_UTILS))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/signal/, $(SIGNAL))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/error/, $(ERROR))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/debug/, $(DEBUG))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/tools/, $(TOOLS))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/tools/cd_pwd/, $(CD_PWD))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/tools/redir_op/, $(REDIR_OP))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/read_line/, $(READ_LINE))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/history/, $(HISTORY))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/term/, $(TERM))) \
				$(addsuffix .c, $(addprefix $(SRC_DIR)/cursor/, $(CURSOR)))

all: $(NAME)

$(NAME):
	$(MAKE) bonus -C $(FT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDE) $(SRCS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	$(MAKE) -C $(FT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(FT_DIR) fclean

re: fclean all

.PHONY:	all clean fclean re bonus
