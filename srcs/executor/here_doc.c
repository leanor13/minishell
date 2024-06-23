/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/23 14:05:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

static int	count_limiters(char **limiters)
{
	int	lim_count;

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

	var()->tmp = &shell;
	lim_count = count_limiters(limiters);
	i = 0;
	while (true)
	{
		line = readline("> ");
		if (line == NULL || (ft_strncmp(line, limiters[i],
					ft_strlen(limiters[i])) == 0
				&& ft_strlen(line) == ft_strlen(limiters[i])))
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

void	here_doc_child(int fd[2], char **limiters, t_shell *shell)
{
	signal(SIGINT, heredoc_sig);
	ft_close(fd[0]);
	read_input(fd, limiters, *shell);
	close_all_unprotected();
	free_shell(shell);
	exit(EXIT_SUCCESS);
}

int	here_doc(t_arg *command, t_shell *shell)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	int		exit_status;

	fd[0] = -1;
	fd[1] = -1;
	status = 0;
	shell->here_doc = true;
	exit_pipe_error(fd);
	pid = fork();
	if (pid < 0)
		ft_error_forking();
	else if (pid == 0)
		here_doc_child(fd, command->here_doc, shell);
	ft_close(fd[1]);
	dup_close(fd[0], STDIN_FILENO);
	wait(&status);
	exit_status = WEXITSTATUS(status);
	if (exit_status == EXIT_HEREDOC_BREAK || exit_status == EXIT_FAILURE)
	{
		free_args(&shell->args_list);
		return (close_all_protected(shell), exit_status);
	}
	return (EXIT_SUCCESS);
}
