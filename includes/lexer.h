#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_arg
{
	char *str; // args
	int	type;
	//char *args; // args = echo "Hello" this is me
	char *in_file; // >> out.txt -> out.txt
	char *out_file; //<< in.txt -> in.txt
	char *here_doc; //
	bool append;
	struct s_arg	*next;
	struct s_arg	*prev;
}				t_arg;

// typedef struct s_arg_pass
// {
// 	char *args; // args = echo "Hello" this is me
// 	char *in_file; // >> out.txt -> out.txt
// 	char *out_file; //<< in.txt -> in.txt
// 	char *here_doc; //
// 	bool append;	//if >> - true, else false;
// 	//char *str; //maybe just simple pointer
// 	int	type;
// 	struct s_arg	*next;
// 	struct s_arg	*prev;
// }				t_arg_pass;

// typedef struct s_arg
// {
// 	char *args; // args = echo "Hello" this is me
// 	char *in_file; // >> out.txt -> out.txt
// 	char *out_file; //<< in.txt -> in.txt

// 	bool here_doc; //
// 	bool append;	//if >> - true, else false;
// 	struct s_arg	*next; // next pipe command, if none - NULL
// 	struct s_arg	*prev; // prev pipe command, if none - NULL
// }				command_for_pipex;
// tyepedef struct command
// {
// 	char			*command;
// 	char			*path;
// 	char			**args;
// }	t_command;

// enum TokenType
// {
// 	CHAR_GENERAL = -1,
// 	CHAR_PIPE = '|',
// 	CHAR_AMPERSAND = '&',
// 	CHAR_QOUTE = '\'',
// 	CHAR_DQUOTE = '\"',
// 	CHAR_SEMICOLON = ';',
// 	CHAR_WHITESPACE = ' ',
// 	CHAR_ESCAPESEQUENCE = '\\',
// 	CHAR_TAB = '\t',
// 	CHAR_NEWLINE = '\n',
// 	CHAR_GREATER = '>',
// 	CHAR_LESSER = '<',
// 	CHAR_NULL = 0,

// 	TOKEN	= -1,
// };

typedef enum e_type
{
	OUTPUT,   //0 integer value// >
	INPUT,    //1 integer value// <
	HEREDOC,  //2 integer valueetc.//<<
	APPEND,   //.../ >>
	PIPE,     // |
	ARG,      // string //EXACT COMMANS? LIKE ECHO STB, AND FLAGS TOO ASK YULIA
	//END       // end of cmd 
	// LPR,      // (
	// RPR,      // )
}t_type;

t_arg	*ft_lexer(char *str);
void	append_node(t_arg **lst, char *str, int end, int len, int value);
t_arg	*ft_parser(t_arg *lst);
void	free_stackfinal(t_arg **lst);

#endif