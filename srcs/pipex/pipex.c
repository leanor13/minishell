/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:26:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 18:27:47 by yioffe           ###   ########.fr       */
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

int exec_command(t_arg *command, t_shell *shell, int *fd_pipe)
{
    int result;
    int original_stdout;

    if (!command)
        return (EXIT_CMD_NOT_FOUND);

    // Handle redirection before checking if it's a built-in or external command
    original_stdout = dup(STDOUT_FILENO);
    if (command->fd_out != STDOUT_FILENO) {
        if (dup2(command->fd_out, STDOUT_FILENO) == -1) {
            perror("dup2 failed for built-in");
            return (EXIT_FAILURE);
        }
    }

    if (command->built_in_fn != NULL) {
        result = command->built_in_fn(shell, command);
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
        if (result != EXIT_SUCCESS)
            return (result);
        if (shell->should_exit && (command->next || command->prev))
            shell->should_exit = false;
        return (EXIT_SUCCESS);
    } else {
        result = handle_parent_process(command, shell, fd_pipe);
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
        return result;
    }
}


int	setup_pipe(t_arg *current, int *fd_pipe, int fd_in)
{
	if (!current->in_file_open || !current->in_file_open[0])
		current->fd_in = fd_in;
	if (current->next)
	{
		if (pipe(fd_pipe) == -1)
		{
			perror("Error creating pipe");
			return (EXIT_FAILURE);
		}
		current->fd_out = fd_pipe[FD_OUT];
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
		close(fd_pipe[FD_OUT]);
		fd_pipe[FD_OUT] = -1;
		*fd_in = fd_pipe[FD_IN];
	}
	else
	{
		close(fd_pipe[FD_IN]);
		close(fd_pipe[FD_OUT]);
		fd_pipe[FD_IN] = -1;
		fd_pipe[FD_OUT] = -1;
		ft_close(*fd_in);
		*fd_in = -1;
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
	return (EXIT_SUCCESS);
}
