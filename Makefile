NAME = pipex

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = pipex/pipex pipex/split_pipex pipex/build_command_list pipex/utils_free_close \
	pipex/utils_misc pipex/here_doc pipex/free_command_list \
	build_ins/ft_cd 

SRCS_PARSING = $(addprefix srcs/,$(addsuffix .c, $(S_PARSING)))
S_PARSING = parsing/main_parsing

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
OBJS_DIR = objs

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBS = $(LIBFT)

# $(TEST_NAME): $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)
# 	@$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)


all: $(NAME)

#parsing: $(NAME_PARSING)

bonus: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: tests/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

# $(BONUS_NAME): $(BONUS_OBJS) $(LIBS)
# 	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME_PARSING): $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME_PARSING) $(SRC) $(LIBS)

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

run: all
	./$(NAME) 

re: fclean all

.PHONY: all fclean clean re