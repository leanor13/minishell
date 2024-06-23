NAME	= minishell

SRCS	= $(addprefix srcs/,$(addsuffix .c, $(FILES)))
FILES	= executor/pipex executor/build_command_list executor/utils_free_close executor/utils_pipe \
	executor/utils_misc executor/here_doc executor/free_command_list executor/check_builtin \
	built_ins/ft_cd built_ins/ft_pwd built_ins/ft_env built_ins/ft_echo \
	built_ins/ft_exit built_ins/ft_export built_ins/ft_unset built_ins/env_helper built_ins/env_helper_2\
	main_flow/init main_flow/main_minishell main_flow/signals main_flow/main_util main_flow/main_util_2\
	main_flow/main_cleanup parsing/lexer parsing/lexer_listutils parsing/parser \
	parsing/lexer_handle_quote parsing/lexer_find_quote parsing/parser_joinlineutils parsing/parser_joinlineutils_args \
	parsing/parser_ifutils parsing/parser_ifutils_2 parsing/lexer_command_scan built_ins/ft_unset_util built_ins/ft_export_util\
	executor/executor_main executor/open_fds built_ins/ft_export_util2

OBJS		= $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))
OBJS_DIR	= objs

CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

INCL	= ./includes/executor.h ./includes/lexer.h ./includes/minishell.h
LIBFT_DIR	= ./includes/libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= $(LIBFT)

GREEN = \033[0;32m
CYAN = \033[0;36m
PURPLE = \033[0;35m
YELLOW = \033[0;33m
NC = \033[0m

all: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBS) $(INCL)
	@echo "$(CYAN)Creating $(NAME) ..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LDFLAGS)
	@echo "✅ $(GREEN)$(NAME) created $(NC)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@$(RM) -r $(OBJS_DIR) $(OBJS_DIR_PARSING)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "✅ $(YELLOW) clean done! $(NC)"

fclean: clean
	@$(RM) $(NAME) $(NAME_PARSING)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "✅ $(YELLOW) fclean done! $(NC)"

re: fclean all

# valgrind:
# 		valgrind --suppressions=valgrind.supp ./minishell

.PHONY: all fclean clean re valgrind parsing
