/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:30:29 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/04 14:08:19 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_process(t_arg *command, t_shell *shell)
{
	int	result;
	struct sigaction sa;

    // Set SIGINT to default or a custom handler if required
    sa.sa_handler = SIG_DFL;  // Default action or use a custom child_sig_handler if defined
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // Ignore SIGQUIT in child
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
	dup_close(command->fd_in, STDIN_FILENO);
	dup_close(command->fd_out, STDOUT_FILENO);
	if (command->built_in_fn)
    {
		result = command->built_in_fn(shell, command);
		free_shell(shell);
		close_all_unprotected();
		exit(result);
    }
	else if (execve(command->path, command->arguments, shell->env_2d) == -1)
	{
		perror("Execve error");
		free_shell(shell);
		close_all_unprotected();
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

pid_t	handle_parent_process(t_arg *command, t_shell *shell, int *fd_pipe)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	if (pid == 0)
	{
		handle_child_process(command, shell);
	}
	else
	{
		
        sa.sa_handler = SIG_IGN;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
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

	last_status = EXIT_SUCCESS;
	close_all_protected(shell);
	if (shell->should_exit)
		return (shell->exit_status);
	while (count > 0)
	{
		child_pid = wait(&status);
		if (child_pid == -1)
		{
			return (EXIT_CMD_NOT_FOUND);
		}
		if (WIFEXITED(status))
		{
			last_status = WEXITSTATUS(status);
		}
		count--;
	}
	return (last_status);
}

int	child_count(t_arg *args_list)
{
	int	i;

	if (!args_list)
		return (0);
	if (args_list->built_in_fn && !args_list->next && !args_list->prev)
		return (0);
	i = 0;
	while (args_list != NULL)
	{
		//if (!args_list->built_in_fn)
		//	i++;
		i ++;
		args_list = args_list->next;
	}
	return (i);
}
