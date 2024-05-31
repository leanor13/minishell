/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:30:29 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 12:34:59 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_process(t_arg *command, t_shell *shell)
{
	if (dup2(command->fd_in, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect standard input");
		exit(EXIT_FAILURE);
	}
	if (dup2(command->fd_out, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect standard output");
		exit(EXIT_FAILURE);
	}
	close_all_protected(shell);
	if (execve(command->path, command->arguments, shell->env_2d) == -1)
	{
		perror("Execve error");
		exit(EXIT_FAILURE);
	}
}

pid_t	handle_parent_process(t_arg *command, t_shell *shell, int *fd_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	if (pid == 0)
	{
		handle_child_process(command, shell);
	}
	else
	{
		if (fd_pipe[FD_OUT] != -1)
		{
			close(fd_pipe[FD_OUT]);
			fd_pipe[FD_OUT] = -1;
		}
		if (command->next == NULL && fd_pipe[FD_IN] != -1)
		{
			close(fd_pipe[FD_IN]);
			fd_pipe[FD_IN] = -1;
		}
	}
	return (pid);
}

int	wait_for_children(int count, t_shell *shell)
{
	int		status;
	int		last_status;
	pid_t	child_pid;

	last_status = 0;
	close_all_protected(shell);
	if (shell->should_exit)
		return (shell->exit_status);
	while (count > 0)
	{
		child_pid = wait(&status);
		if (child_pid == -1)
			return (EXIT_CMD_NOT_FOUND);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = EXIT_SIGNAL_OFFSET + WTERMSIG(status);
		count--;
	}
	return (last_status);
}
