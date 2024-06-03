/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:26:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/03 16:29:36 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

/* // debugging function, printf can be uncommented to monitor fds
void	print_open_fds(char *message)
{
	int			fd;
	struct stat	stats;
	int			result;
	int			original_stdout;

	(void)message;
	printf("Open file descriptors (%s):\n", message);
	for (fd = 0; fd < getdtablesize(); fd++)
	{
		if (fstat(fd, &stats) == 0)
		{
			printf("fd %d is open\n", fd);
		}
	}
} */
int	exec_command(t_arg *command, t_shell *shell, int *fd_pipe)
{
	int	result;
	int	original_stdout;
	int	original_stdin;

	if (!command)
		return (EXIT_CMD_NOT_FOUND);
	if (command->built_in_fn != NULL && !command->prev && !command->next)
	{
		original_stdout = dup(STDOUT_FILENO);
		original_stdin = dup(STDIN_FILENO);
		dup_close(command->fd_in, STDIN_FILENO);
		dup_close(command->fd_out, STDOUT_FILENO);
		result = command->built_in_fn(shell, command);
		dup_close(original_stdin, STDIN_FILENO);
		dup_close(original_stdout, STDOUT_FILENO);
		shell->exit_status = result;
		if (result != EXIT_SUCCESS)
			return (result);
		//if (shell->should_exit && (command->next || command->prev))
		//	shell->should_exit = false;
		close_all_protected(shell);
		return (EXIT_SUCCESS);
	}
	else
		return (handle_parent_process(command, shell, fd_pipe));
}

int	setup_pipe(t_arg *current, int *fd_pipe, int fd_in)
{
	if (!current->in_file || !current->in_file[0])
		current->fd_in = fd_in;
	if (current->next)
	{
		if (pipe(fd_pipe) == -1)
		{
			perror("Error creating pipe");
			return (EXIT_FAILURE);
		}
		if (!current->out_file || !current->out_file[0])
			current->fd_out = fd_pipe[FD_OUT];
		if (!current->next->in_file || !current->next->in_file[0])
			current->next->fd_in = fd_pipe[FD_IN];
	}
	else if (!current->out_file || !current->out_file[0])
		current->fd_out = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}

void	execute_current_command(t_arg *current, t_shell *shell, int *fd_pipe,
		int *fd_in)
{
	int	result;

	result = exec_command(current, shell, fd_pipe);
	if (result < 0)
		return ;
	if (current->next)
	{
		ft_close(fd_pipe[FD_OUT]);
		*fd_in = fd_pipe[FD_IN];
	}
	else
	{
		ft_close(fd_pipe[FD_IN]);
		ft_close(fd_pipe[FD_OUT]);
		ft_close(*fd_in);
	}
}

void	process_commands(t_shell *shell, t_arg *current, int *fd_pipe,
		int *fd_in)
{
	while (current)
	{
		if (current->command)
		{
			if (setup_pipe(current, fd_pipe, *fd_in) == NEG_ERROR)
			{
				close_all_protected(shell);
				return ;
			}
			execute_current_command(current, shell, fd_pipe, fd_in);
		}
		current = current->next;
	}
}

int	exec_pipe(t_shell *shell)
{
	int		fd_in;
	t_arg	*current;
	int		count;
	t_arg	*c_list;
	int		fd_pipe[2];

	fd_pipe[FD_IN] = -1;
	fd_pipe[FD_OUT] = -1;
	fd_in = STDIN_FILENO;
	c_list = shell->args_list;
	if (!c_list)
		return (EXIT_CMD_NOT_FOUND);
	current = c_list;
	count = child_count(c_list);
	process_commands(shell, current, fd_pipe, &fd_in);
	shell->exit_status = wait_for_children(count, shell);
	close_all_protected(shell);
	return (shell->exit_status);
}
