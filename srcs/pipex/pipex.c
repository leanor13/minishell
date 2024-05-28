/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/28 12:38:18 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

// debugging function, printf can be uncommented to monitor fds
void	print_open_fds(char *message)
{
	int			fd;
	struct stat	stats;

	(void)message;
	// printf("Open file descriptors (%s):\n", message);
	for (fd = 0; fd < getdtablesize(); fd++)
	{
		if (fstat(fd, &stats) == 0)
		{
			// printf("fd %d is open\n", fd);
		}
	}
}

void	close_fds_except(int fd1, int fd2, int fd3, int fd4, int fd5)
{
	for (int fd = 3; fd < getdtablesize(); fd++)
	{
		if (fd != fd1 && fd != fd2 && fd != fd3 && fd != fd4 && fd != fd5)
		{
			close(fd);
		}
	}
}

void	close_fds_post_dup(int old_fd)
{
	if (old_fd > STDERR_FILENO)
	{ // Generally, avoid closing standard fds (0, 1, 2)
		close(old_fd);
		// printf("Closed fd: %d\n", old_fd);
		// Debug message to confirm closure
	}
}

void	handle_child_process(t_arg *command, t_shell *shell)
{
	// printf("Child process for command: %s\n", command->command);
	// printf("Child dup_close fd_in: %d -> STDIN, fd_out: %d -> STDOUT\n",
	//	command->fd_in, command->fd_out);
	print_open_fds("handle_child_process: before dup2");
	if (dup2(command->fd_in, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect standard input");
		exit(EXIT_FAILURE);
	}
	close_fds_post_dup(command->fd_in);
	if (dup2(command->fd_out, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect standard output");
		exit(EXIT_FAILURE);
	}
	close_fds_post_dup(command->fd_out);
	print_open_fds("handle_child_process: after dup2 and close");
	close_fds_except(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, -1, -1);
	print_open_fds("handle_child_process: before close protected");
	close_all_protected(shell);
	print_open_fds("handle_child_process: after close protected");
	if (execve(command->path, command->arguments, shell->env_2d) == -1)
	{
		perror("Execve error");
		exit(NEG_ERROR);
	}
	print_open_fds("handle_child_process execve failed");
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

int	exec_command(t_arg *command, t_shell *shell, int *fd_pipe)
{
	int	result;

	if (!command)
		return (NEG_ERROR);
	if (command->built_in_fn != NULL)
	{
		result = command->built_in_fn(shell, command);
		if (result == EXIT_FAILURE)
		{
			ft_putstr_nl("Built-in error\n", STDERR_FILENO);
			return (NEG_ERROR);
		}
		if (shell->should_exit && (command->next || command->prev))
			shell->should_exit = false;
		return (EXIT_SUCCESS);
	}
	else
	{
		return (handle_parent_process(command, shell, fd_pipe));
	}
}

int	setup_pipe(t_arg *current, int *fd_pipe, int fd_in)
{
	if (!current->in_file_open || !current->in_file_open[0])
		current->fd_in = fd_in;
	if (current->next) // check if we need to create a pipe
	{
		print_open_fds("setup_pipe: right before pipe");
		if (pipe(fd_pipe) == -1)
		{
			perror("Error creating pipe");
			return (NEG_ERROR);
		}
		print_open_fds("setup_pipe: right after pipe creation");
		if (!current->out_file || !current->out_file[0])
			current->fd_out = fd_pipe[FD_OUT];
	}
	else if (!current->out_file || !current->out_file[0])
		current->fd_out = STDOUT_FILENO;
	print_open_fds("setup_pipe: end of function");
	return (EXIT_SUCCESS);
}

int	wait_for_children(int count, t_shell *shell)
{
	int		status;
	int		last_status;
	pid_t	child_pid;

	close_all_protected(shell);
	last_status = 0;
	if (shell->should_exit)
		return (shell->exit_status);
	while (count > 0)
	{
		child_pid = wait(&status);
		if (child_pid == -1)
			return (-1);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (last_status != 0)
			return (last_status);
		count--;
	}
	return (last_status);
}

void	close_pipes(int *fd_pipe)
{
	if (fd_pipe[FD_IN] >= 0)
	{
		// printf("Closing pipe input fd: %d\n", fd_pipe[FD_IN]);
		close(fd_pipe[FD_IN]);
		fd_pipe[FD_IN] = -1; // Mark as closed
	}
	if (fd_pipe[FD_OUT] >= 0)
	{
		// printf("Closing pipe output fd: %d\n", fd_pipe[FD_OUT]);
		close(fd_pipe[FD_OUT]);
		fd_pipe[FD_OUT] = -1; // Mark as closed
	}
}

void	close_if_needed(int fd)
{
	if (fd >= 0)
	{
		// printf("Closing fd: %d\n", fd);
		close(fd);
	}
}

void	execute_current_command(t_arg *current, t_shell *shell, int *fd_pipe,
		int *fd_in)
{
	if (exec_command(current, shell, fd_pipe) < 0)
	{
		close_pipes(fd_pipe);
	}
	else
	{
		if (fd_pipe[FD_OUT] != -1)
		{
			close(fd_pipe[FD_OUT]);
			fd_pipe[FD_OUT] = -1;
		}
		if (current->next)
		{
			*fd_in = fd_pipe[FD_IN];
		}
		else
		{
			if (fd_pipe[FD_IN] != -1)
			{
				close(fd_pipe[FD_IN]);
				fd_pipe[FD_IN] = -1;
			}
			close_if_needed(*fd_in);
			*fd_in = -1;
		}
	}
}

void	process_commands(t_shell *shell, t_arg *current, int *fd_pipe,
		int *fd_in)
{
	while (current)
	{
		if (current->command)
		{
			// printf("command: %s\n", current->command);
			if (setup_pipe(current, fd_pipe, *fd_in) == NEG_ERROR)
			{
				close_all_protected(shell);
				return ;
			}
			print_open_fds("process_commands: process current command");
			execute_current_command(current, shell, fd_pipe, fd_in);
		}
		current = current->next;
	}
	print_open_fds("process_commands: after processing all commands");
}

int	exec_pipe(t_shell *shell)
{
	int		fd_in;
	t_arg	*current;
	int		count;
	t_arg	*c_list;
	int		fd_pipe[2] = {-1, -1};

	fd_in = STDIN_FILENO;
	c_list = shell->args_list;
	if (!c_list)
		return (NEG_ERROR);
	current = c_list;
	count = args_count(c_list);
	process_commands(shell, current, fd_pipe, &fd_in);
	print_open_fds("exec_pipe: before close and wait");
	close_if_needed(fd_in);
	shell->exit_status = wait_for_children(count, shell);
	print_open_fds("exec_pipe: end of the function");
	return (EXIT_SUCCESS);
}
