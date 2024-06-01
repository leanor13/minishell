/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/01 11:23:44 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

# ifndef PATH_MAX
#  define PATH_MAX 256
# endif

# define CHILD_PID 0
# define NEG_ERROR -1
# define FD_IN 0
# define FD_OUT 1
# define PRINT_PIPE_ERROR true
# define HERE_DOC 0
# define INPUT_FILE 1
# define OUTPUT_REWRITE 2
# define OUTPUT_APPEND 3

# define WRONG_ARG_NUM "Wrong number of arguments. \
Usage: ./pipex file1 cmd1 cmd2 file2 or \
./pipex here_doc LIMITER cmd cmd1 file \n"
# define ERR_NESTED_QUOTES "Syntax error: nested quotes"
# define ERR_SINGLE_QUOTE "Syntax error: single quote"
# define EMPTY_ENV ": No such file or directory\n"
# define ENV_PARSING "Environment can't be parsed\n"

typedef struct command
{
	char			*command;
	char			*path;
	char			**args;
	int				(*built_in_fn)(char **env, char **args, int fd);
	int				input_file;
	int				output_file;
}	t_command;

//int			main_pipex(int ac, char **av, char **env);

#endif