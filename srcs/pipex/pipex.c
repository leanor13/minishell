/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/24 13:42:20 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

void print_open_fds() 
{
    int fd;
    struct stat stats;
    printf("Open file descriptors:\n");
    for (fd = 0; fd < getdtablesize(); fd++) {
        if (fstat(fd, &stats) == 0) {
            printf("fd %d is open\n", fd);
        }
    }
}

void handle_child_process(t_arg *command, t_shell *shell)
{
    printf("Child process for command: %s\n", command->command);
    printf("Child dup_close fd_in: %d -> STDIN, fd_out: %d -> STDOUT\n", command->fd_in, command->fd_out);

    if (dup2(command->fd_in, STDIN_FILENO) == -1 || dup2(command->fd_out, STDOUT_FILENO) == -1) {
        perror("dup2 failed");
        exit(EXIT_FAILURE);
    }
    ft_close(command->fd_in);
    ft_close(command->fd_out);
	//print_open_fds();
	close_all_protected(shell);
	//print_open_fds();
    if (command->built_in_fn != NULL)
    {
        if (command->built_in_fn(shell, command) == EXIT_FAILURE)
        {
            fprintf(stderr, "Built-in error\n");
            exit(NEG_ERROR);
        }
        else
            exit(EXIT_SUCCESS);
    }
    else if (execve(command->path, command->arguments, shell->env_2d) == -1)
    {
        perror("Execve error");
        exit(NEG_ERROR);
    }
    // No need to call close_all_unprotected here, as execve will replace the process image.
}


pid_t handle_parent_process(t_arg *command, t_shell *shell)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	if (pid == 0)
	{
		handle_child_process(command, shell);
	}
	return pid;
}

int exec_command(t_arg *command, t_shell *shell)
{
	pid_t pid;

	if (!command)
		return (NEG_ERROR);
	pid = handle_parent_process(command, shell);
	return pid;
}

int setup_pipe(t_arg *current, int *fd_pipe, int fd_in)
{
	if (!current->in_file_open || !current->in_file_open[0])
		current->fd_in = fd_in;
	if (pipe(fd_pipe) == -1)
	{
		perror("Error creating pipe");
		return (NEG_ERROR);
	}
	if (current->next == NULL && (!current->out_file || !current->out_file[0]))
		current->fd_out = STDOUT_FILENO;
	else if (!current->out_file || !current->out_file[0])
		current->fd_out = fd_pipe[FD_OUT];
	
	printf("command: %s, fd_in: %d, fd_out: %d, pipe_in: %d, pipe_out: %d\n",
		   current->command, current->fd_in, current->fd_out, fd_pipe[FD_IN], fd_pipe[FD_OUT]);
	return (EXIT_SUCCESS);
}

void wait_for_children(int count)
{
	int status;

	printf("wait starts\n");
	//print_open_fds();
	while (count > 0)
	{
		wait(&status);
		count--;
	}
}

void close_pipes(int fd_in, int *fd_pipe)
{
	ft_close(fd_pipe[FD_OUT]);
	ft_close(fd_in);
}

void execute_current_command(t_arg *current, t_shell *shell, int *fd_pipe, int *fd_in)
{
    if (exec_command(current, shell) < 0)
    {
        close_pipes(*fd_in, fd_pipe);
        if (current->next)
            *fd_in = fd_pipe[FD_IN];
        current = current->next;
    }
    if (current->next)
        *fd_in = fd_pipe[FD_IN];
    ft_close(fd_pipe[FD_OUT]);
}

void process_commands(t_shell *shell, t_arg *current, int *fd_pipe, int *fd_in)
{
    while (current)
    {
        if (current->command)
        {
            printf("command: %s\n", current->command);
            if (setup_pipe(current, fd_pipe, *fd_in) == NEG_ERROR)
            {
                close_all_protected(shell);
                return;
            }
			//print_open_fds();
            execute_current_command(current, shell, fd_pipe, fd_in);
        }
        current = current->next;
    }
}

int exec_pipe(t_shell *shell)
{
    int fd_pipe[2];
    int fd_in;
    t_arg *current;
    int count;
    t_arg *c_list;

    fd_in = STDIN_FILENO;
    c_list = shell->args_list;
    if (!c_list)
        return (NEG_ERROR);
    current = c_list;
    count = args_count(c_list);
    process_commands(shell, current, fd_pipe, &fd_in);
	//print_open_fds();
    ft_close(fd_in);
    wait_for_children(count);
    return (EXIT_SUCCESS);
}


/*	for (i = 0; i < count; i++)
	{
		int child_status;
		waitpid(-1, &child_status, 0);
		if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != EXIT_SUCCESS)
			status = EXIT_FAILURE;
		shell->exit_status = child_status;
	} 
	return (status);
} */


