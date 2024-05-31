/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 16:36:16 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell	t_shell;

typedef struct s_arg
{
	char			*str; // args in the lexer
	int				type; //assign type in the lexer
	char			**arguments;
	char			*in_file; // >>  > out.txt -> out.txt
	char			**out_file; //< in.txt -> in.txt
	char			**in_file_open; //< in.txt -> in.txt
	char			**here_doc; // << first one is going ot be an argument so it nice in this way
	bool			append; // it is only a bool if the last on is append other thatn that they are outputfiles 
	char			*command; // used in executor
	char			*path; // used in executor
	int				fd_in;
	int				fd_out;
	int				(*built_in_fn)(t_shell *shell, struct s_arg *command);
	struct s_arg	*next;
	struct s_arg	*prev;
}				t_arg;

typedef struct s_append
{
	int				start;
	int				len;
}				t_append;

typedef struct s_sign
{
	int	quote_type;
}				t_sign;

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
}				t_type;

t_arg	*ft_lexer(char *str, t_arg *lst);
void	append_node(t_arg **lst, char *str, t_append info, int value);
t_arg	*ft_parser(t_arg *lst, t_shell *shell);
void	free_stackfinal(t_arg **lst);
t_arg	*ft_stacklast(t_arg *lst);
void	ft_printsyntaxerror(t_arg **lst);
int		find_quote(t_sign **lst, char *str, int i);
int		handle_quotestring(t_arg **lst, t_sign **quote, char *str, int i);
char	**ft_strjoinline_args(t_arg *lst, int i, t_shell *shell);
char	**ft_strjoinline_heredoc(t_arg *lst, int i);
char	**ft_strjoinline_output(t_arg *lst, int i);
char	**ft_strjoinline_input(t_arg *lst, int i);

#endif
