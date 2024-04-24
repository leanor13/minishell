NAME	= pipex

SRCS	= $(addprefix srcs/,$(addsuffix .c, $(FILES)))
FILES	= pipex/pipex pipex/split_pipex pipex/build_command_list pipex/utils_free_close \
	pipex/utils_misc pipex/here_doc pipex/free_command_list pipex/check_builtin \
	built_ins/ft_cd built_ins/ft_pwd built_ins/ft_env built_ins/get_current_pwd  built_ins/ft_echo \
	built_ins/ft_exit built_ins/ft_export built_ins/ft_unset \
	main_flow/init main_flow/main_minishell \
	parsing/main_parsing_yulia

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
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS = -lreadline

LIBFT_DIR	= ./includes/libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= $(LIBFT)

all: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

parsing: $(NAME_PARSING)

$(OBJS_DIR_PARSING)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME_PARSING): $(OBJS_PARSING) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME_PARSING) $(OBJS_PARSING) $(LIBS) $(LDFLAGS)

clean:
	@$(RM) -r $(OBJS_DIR) $(OBJS_DIR_PARSING)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME) $(NAME_PARSING)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

# valgrind:
# 		valgrind --suppressions=valgrind.supp ./parsing

valgrind:
		valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=all ./parsing

.PHONY: all fclean clean re valgrind parsing

# $(TEST_NAME): $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)
# 	@$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)

#------------------------------------------------------------OLD VERSION---------------------------------------------------------------------------------
# NAME = pipex

# SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
# S = pipex/pipex pipex/split_pipex pipex/build_command_list pipex/utils_free_close \
# 	pipex/utils_misc pipex/here_doc pipex/free_command_list \
# 	built_ins/ft_cd 

# SRCS_PARSING = $(addprefix srcs/,$(addsuffix .c, $(S_PARSING)))
# S_PARSING = parsing/main_parsing

# COMPRESS = ar rcs
# RM = rm -f
# CFLAGS = -Wall -Wextra -Werror -g3
# CC = cc

# OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

# BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
# OBJS_DIR = objs

# LIBFT_DIR = ./includes/libft
# LIBFT = $(LIBFT_DIR)/libft.a

# LIBS = $(LIBFT)

# # $(TEST_NAME): $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)
# # 	@$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)


# all: $(NAME)

# #parsing: $(NAME_PARSING)

# bonus: $(NAME)

# $(OBJS_DIR)/%.o: srcs/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(OBJS_DIR)/%.o: tests/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJS) $(LIBS)
# 	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

# # $(BONUS_NAME): $(BONUS_OBJS) $(LIBS)
# # 	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBS)

# $(LIBFT):
# 	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

# $(NAME_PARSING): $(OBJS) $(LIBS)
# 	@$(CC) $(CFLAGS) -o $(NAME_PARSING) $(SRC) $(LIBS)

# clean:
# 	@$(RM) -r $(OBJS_DIR)
# 	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

# fclean: clean
# 	@$(RM) $(NAME)
# 	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

# run: all
# 	./$(NAME) 

# re: fclean all

# .PHONY: all fclean clean re
