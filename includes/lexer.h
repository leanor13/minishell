/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:21:43 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/04 14:16:48 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

typedef struct s_shell	t_shell;

typedef struct s_arg
{
	char				*str;
	int					type;
	char				**arguments;
	char				**out_file;
	char				**in_file;
	char				**here_doc;
	bool				append;
	char				*command;
	char				*path;
	int					fd_in;
	int					fd_out;
	int					(*built_in_fn)(t_shell *shell, struct s_arg *command);
	struct s_arg		*next;
	struct s_arg		*prev;
}						t_arg;

typedef struct s_append
{
	int					start;
	int					len;
}						t_append;

typedef struct s_sign
{
	int					quote_type;
}						t_sign;

# define NONE_TYPE 0
# define FIRST_DOUBLE_QUOTE 2
# define FIRST_SINGLE_QUOTE 3
# define SECOND_DOUBLE_QUOTE 4
# define SECOND_SINGLE_QUOTE 5

typedef enum e_type
{
	OUTPUT,
	INPUT,
	HEREDOC,
	APPEND,
	PIPE,
	ARG,
	GOING_ARG,
	GOING_HEREDOC,
	GOING_INPUT,
	GOING_OUTPUT,
	DOUBLE_PIPE,
	DOLLAR_SIGN,
	GOING_DOLLAR_SIGN,
	SINGLEQUOTE_DOLLAR,
	GOING_SINGLEQUOTE_DOLLAR,
	WRONG,
}						t_type;

t_arg					*ft_lexer(char *str, t_arg *lst);
void					append_node(t_arg **lst, char *str, t_append info,
							int value);
t_arg					*ft_parser(t_arg *lst, t_shell *shell);
void					free_stackfinal(t_arg **lst);
t_arg					*ft_stacklast(t_arg *lst);
void					ft_printsyntaxerror(t_arg **lst);
int						find_quote(t_sign **lst, char *str, int i);
int						handle_quotestring(t_arg **lst, t_sign **quote,
							char *str, int i);
char					**ft_strjoinline_args(t_arg *lst, int i,
							t_shell *shell);
char					**ft_strjoinline_heredoc(t_arg *lst, int i);
char					**ft_strjoinline_output(t_arg *lst, int i);
char					**ft_strjoinline_input(t_arg *lst, int i);

#endif
