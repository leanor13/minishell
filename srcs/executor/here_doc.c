/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/18 17:40:12 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_line(t_shell *shell)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
	{
		close_all_unprotected();
		free_shell(shell);
		perror("Error reading from standard input");
		exit(EXIT_FAILURE);
	}
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

static void	read_input(int fd[2], char **limiters, t_shell shell)
{
	char	*line;
	int		lim_count;
	int		i;

	lim_count = count_limiters(limiters);
	i = 0;
	ft_close(fd[0]);
	while (true)
	{
		write(shell.std_fds[FD_OUT], "> ", 2);
		line = get_line(&shell);
		if (strncmp(line, limiters[i], strlen(limiters[i])) == 0
			&& strlen(line) == strlen(limiters[i]) + 1)
		{
			free(line);
			i++;
			if (i == lim_count)
				break ;
			continue ;
		}
		if (i == lim_count - 1)
			write(fd[1], line, ft_strlen(line));
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
	int		fd[2];
	int		status;
	char	**limiters;

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
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		return (close_all_protected(shell), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
