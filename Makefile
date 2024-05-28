NAME	= minishell

SRCS	= $(addprefix srcs/,$(addsuffix .c, $(FILES)))
FILES	= pipex/pipex pipex/split_pipex pipex/build_command_list pipex/utils_free_close \
	pipex/utils_misc pipex/here_doc pipex/free_command_list pipex/check_builtin \
	built_ins/ft_cd built_ins/ft_pwd built_ins/ft_env built_ins/get_current_pwd  built_ins/ft_echo \
	built_ins/ft_exit built_ins/ft_export built_ins/ft_unset built_ins/env_helper built_ins/env_helper_2\
	main_flow/init main_flow/main_minishell \
	parsing/main_parsing parsing/lexer parsing/lexer_listutils parsing/parser cleanup/main_cleanup\
	executor/executor_main executor/open_fds

OBJS		= $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))
OBJS_DIR	= objs

NAME_PARSING	= parsing

SRCS_PARSING	= $(addprefix srcs/,$(addsuffix .c, $(FILES_PARSING)))
FILES_PARSING	= parsing/main_parsing parsing/lexer parsing/lexer_listutils
# parsing/parser

OBJS_PARSING		= $(addprefix $(OBJS_DIR_PARSING)/,$(SRCS_PARSING:srcs/%.c=%.o))
OBJS_DIR_PARSING	= objs_parsing

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


parsing: $(NAME_PARSING)

$(OBJS_DIR_PARSING)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "✅ $(GREEN)$@ created $(NC)"

$(NAME_PARSING): $(OBJS_PARSING) $(LIBS)
	@echo "$(CYAN)Creating $(NAME_PARSING) ..."
	@$(CC) $(CFLAGS) -o $(NAME_PARSING) $(OBJS_PARSING) $(LIBS) $(LDFLAGS)
	@echo "✅ $(GREEN)$(NAME_PARSING) created $(NC)"

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
# 		valgrind --suppressions=valgrind.supp ./parsing

valgrind:
		valgrind --suppressions=valgrind.supp --trace-children=yes  --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=all ./minishell

.PHONY: all fclean clean re valgrind parsing
