/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:02:16 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/01 16:41:37 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd != -1 && fd != STDERR_FILENO && fd != STDIN_FILENO
		&& fd != STDOUT_FILENO)
		close(fd);
}

void	close_all_protected(t_shell *shell)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		if (i != shell->std_fds[0] && i != shell->std_fds[1]
			&& i != shell->std_fds[2])
			ft_close(i);
		i++;
	}
}

void	close_all_unprotected(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

void	exit_pipe_error(int fd[2])
{
	if (pipe(fd) < 0)
	{
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_pipes(int *fd_pipe)
{
	if (fd_pipe[FD_IN] >= 0)
	{
		ft_close(fd_pipe[FD_IN]);
	}
	if (fd_pipe[FD_OUT] >= 0)
	{
		ft_close(fd_pipe[FD_OUT]);
	}
}
