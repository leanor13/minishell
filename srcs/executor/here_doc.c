/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/21 21:09:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

t_shell* var()
{
	static t_shell tmp;
	return(&tmp);
}
static char	*get_line(t_shell *shell)
{
	char	*line;

	line = readline("> ");
	return (line);
}

static int	count_limiters(char **limiters)
{
	int		lim_count;

	lim_count = 0;
	while (limiters[lim_count])
		lim_count++;
	return (lim_count);
}

void alex(int code)
{
	if (code == SIGINT)
	{
		// printf("alex\n");
		free_shell(var()->tmp);
		exit(EXIT_HEREDOC_BREAK);
	}
	// return(0);
}

static void	read_input(int fd[2], char **limiters, t_shell shell)
{
	char	*line;
	int		lim_count;
	int		i;

	signal(SIGINT, alex);
	var()->tmp = &shell;
	lim_count = count_limiters(limiters);
	i = 0;
	ft_close(fd[0]);
	while (true)
	{
		// write(shell.std_fds[FD_OUT], "> ", 2);
		line = get_line(&shell);
		
		if (line == NULL || (strncmp(line, limiters[i], strlen(limiters[i])) == 0
			&& strlen(line) == strlen(limiters[i])))
		{
			free(line);
			i++;
			if (i == lim_count)
				break ;
			continue ;
		}

		if (i == lim_count - 1)
			ft_putstr_nl(line, fd[1]);
		
		free(line);
	}
	ft_close(fd[1]);
}

static void	ft_error_forking(void)
{
	perror("Error forking");
	exit(EXIT_FAILURE);
}

int	here_doc(t_arg *command, t_shell *shell)
{
	pid_t	pid;
	int	fd[2];
	int	status;
	char	**limiters;

	fd[0] = -1;
	fd[1] = -1;
	status = 0;
	limiters = command->here_doc;
	shell->here_doc = true;
	exit_pipe_error(fd);
	pid = fork();
	if (pid < 0)
		ft_error_forking();
	else if (pid == 0)
	{
		read_input(fd, limiters, *shell);
		close_all_unprotected();
		free_shell(shell);
		exit(EXIT_SUCCESS);
	}
	ft_close(fd[1]);
	dup_close(fd[0], STDIN_FILENO);
	wait(&status);
	if (WEXITSTATUS(status) == EXIT_HEREDOC_BREAK)
	{
		free_args(&shell->args_list);
		return (close_all_protected(shell), EXIT_HEREDOC_BREAK);
	}
	if (WEXITSTATUS(status) == EXIT_FAILURE)
	{
		free_args(&shell->args_list);
		return (close_all_protected(shell), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
