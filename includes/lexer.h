/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:21:43 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/16 14:23:42 by thuy-ngu         ###   ########.fr       */
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

typedef struct s_export
{
	int					i;
	int					sign;
	size_t				name_len;
	char				**args;
	char				*equal_sign;
}						t_export;

typedef struct s_heads
{
	t_arg	*head_arg;
	t_arg	*head_heredoc;
	t_arg	*head_output;
	t_arg	*head_input;
	int		i;
	int		j;
	int		k;
	int		l;
}			t_heads;

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

void		if_strjoin(t_heads heads, t_arg **node, t_shell *shell);
int			if_heredoc(t_arg **lst, t_arg **node, \
t_arg **temp_lst, t_heads *heads);
void		if_arg(t_arg **lst, t_heads *heads);
int			if_output(t_arg **lst, t_arg **node, \
t_arg **temp_lst, t_heads *heads);
int			if_input(t_arg **lst, t_arg **node, \
t_arg **temp_lst, t_heads *heads);
int			if_append(t_arg **lst, t_arg **node, \
t_arg **temp_lst, t_heads *heads);
void		if_dollarsign(t_arg **lst, t_heads *heads);
int			if_doublepipe(t_arg **lst, t_arg **node, t_arg **temp_lst);
int			if_pipe(t_arg **lst, t_arg **node, t_arg **temp_lst);
t_arg		*ft_lexer(char *str, t_arg *lst);
void		append_node(t_arg **lst, char *str, t_append info, int value);
t_arg		*ft_parser(t_arg *lst, t_shell *shell);
t_arg		*ft_stacklast(t_arg *lst);
void		ft_printsyntaxerror(t_arg **lst);
int			find_quote(t_sign **lst, char *str, int i);
int			handle_quotestring(t_arg **lst, t_sign **quote, char *str, int i);
char		**ft_strjoin_args(t_arg *lst, int i, t_shell *shell);
char		**ft_strjoin_heredoc(t_arg *lst, int i);
char		**ft_strjoin_output(t_arg *lst, int i);
char		**ft_strjoin_input(t_arg *lst, int i);
void		connect_last(t_arg **node, t_arg **final);
int			shellcommand_scan(t_arg **lst, char *str, int i, t_sign **quote);
int			arg_scan(t_arg **lst, char *str, int i, t_sign **quote);
int			skip_space(char *str, int i);

#endif