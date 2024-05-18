/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/18 13:41:16 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_command(t_arg *command, t_shell *shell)
{
	pid_t	pid;

	if (!command)
		return (NEG_ERROR);
	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	if (pid == 0)
	{
		//printf("child start\n");
		dup_close(command->fd_in, STDIN_FILENO);
		dup_close(command->fd_out, STDOUT_FILENO);
		//printf("command: %s, fd_in:%d, fd_out: %d\n", 
		//	command->command, command->fd_in, command->fd_out);
		//printf("child finish\n");
		if (command->built_in_fn != NULL)
		{
			if (command->built_in_fn(shell, command) == EXIT_FAILURE)
			{
				ft_putstr_nl("Built-in error", STDERR_FILENO);
				exit (NEG_ERROR);
			}
			else
				exit (EXIT_SUCCESS);
		}
		else if (execve(command->path, command->arguments, shell->env_2d) == -1)
		{
			perror("Execve error");
			//printf("path: %s", command->path);
			exit (NEG_ERROR);
		}
	}
	return (pid);
}

int exec_pipe(t_shell *shell)
{
	int fd_pipe[2];
	int status = EXIT_SUCCESS;
	t_arg *current;
	int count;
	int i;
	t_arg *c_list = shell->args_list;
	int fd_in = 0;

	if (!c_list)
		return (NEG_ERROR);
	current = c_list;
	count = args_count(c_list);
	while (current)
	{
		if (current->command)
		{
			if (!current->in_file_open || !current->in_file_open[0])
			// && !(current->prev && current->prev->here_doc))
				current->fd_in = fd_in;
			//else if (!current->in_file && current->prev && current->prev->here_doc)
			//{
			//	current->fd_in = STDIN_FILENO;
			//	//printf("current heredoc\n");
			//}
			//printf("current->command: %s\n", current->command);
			if (pipe(fd_pipe) == -1)
			{
				perror("Error creating pipe");
				return (close_all_protected(shell), NEG_ERROR);
			}
			if (current->next == NULL && (!current->out_file || !current->out_file[0]))
				current->fd_out = STDOUT_FILENO;
			else if (!current->out_file || !current->out_file[0])
				current->fd_out = fd_pipe[FD_OUT];
			//printf("command %s: fd_out: %d\n", current->command, current->fd_out);
			if (exec_command(current, shell) < 0)
			{
				//printf("closing fd_pipe[FD_OUT]: %d\n", fd_pipe[FD_OUT]);
				ft_close(fd_pipe[FD_OUT]);
				if (current->next != NULL)
				{
					//printf("closing fd_in: %d\n", fd_in);
					ft_close(fd_in);
				}
				current = current->next;
				continue;
			}
			if (!current->out_file || !current->out_file[0])
			{
				fd_in = fd_pipe[FD_IN];
			}
			//printf("closing fd_pipe[FD_OUT]: %d\n", fd_pipe[FD_OUT]);
			ft_close(fd_pipe[FD_OUT]);
		}
		current = current->next;
	}
	//printf("closing fd_in: %d\n", fd_in);
	ft_close(fd_in);
	for (i = 0; i < count; i++)
    {
        int child_status;
        waitpid(-1, &child_status, 0);
        if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != EXIT_SUCCESS)
            status = EXIT_FAILURE; // Added comment: Update status if any child process failed
    }
	return (status);
}

/* int	open_file(int ac, char **av, int type)
{
	int	fd;

	fd = 0;
	if (type == HERE_DOC)
		fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == OUTPUT_REWRITE)
		fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == INPUT_FILE)
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		if (type == INPUT_FILE)
			perror("Failed opening input file");
		else
			perror("Failed opening output file");
		return (NEG_ERROR);
	}
	return (fd);
} */

int			open_file(char *file, int type)
{
	int	fd;

	if (!file)
		return (0);
	fd = 0;
	if (type == HERE_DOC || type == OUTPUT_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == OUTPUT_REWRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == INPUT_FILE)
		fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		if (type == INPUT_FILE)
			perror("Failed opening input file");
		else
			perror("Failed opening output file");
		return (NEG_ERROR);
	}
	return (fd);
}

