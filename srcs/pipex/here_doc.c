/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/14 16:53:25 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void read_input(int fd[2], char *limiter)
{
	char *line;

	close(fd[0]); // Close the read end of the pipe in the child process
	while (true)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			// free something
			close_all_unprotected();
			perror("Error reading from standard input");
			exit(EXIT_FAILURE);
		}
		if (strncmp(line, limiter, strlen(limiter)) == 0 && strlen(line) == strlen(limiter) + 1)
		{
			free(line);
			break;
		}
		write(fd[1], line, strlen(line));
		free(line);
	}
	close(fd[1]); // Close the write end of the pipe in the child process
}


static void	ft_error_forking(void)
{
	perror("Error forking");
	exit (EXIT_FAILURE);
}

int here_doc(t_arg *command, t_shell *shell)
{
	pid_t pid;
	int fd[2];
	int status;
	char *limiter = command->here_doc;

	shell->here_doc = true;
	if (pipe(fd) == -1) // Create a pipe
	{
		perror("Error creating pipe");
		return EXIT_FAILURE;
	}
	pid = fork();
	if (pid < 0)
		ft_error_forking();
	else if (pid == 0)
	{
		close(fd[0]); // Close the read end in the child process
		read_input(fd, limiter);
		close(fd[1]); // Close the write end after writing is done
		close_all_unprotected();
		exit(EXIT_SUCCESS);
	}
	close(fd[1]); // Close the write end in the parent process
	if (dup2(fd[0], STDIN_FILENO) == -1) // Redirect stdin to read from the pipe
	{
		perror("dup2");
		close(fd[0]); // Close the read end if dup2 fails
		return EXIT_FAILURE;
	}
	close(fd[0]); // Close the read end after dup2
	wait(&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		// free if needed
		close_all_protected();
		return EXIT_FAILURE;
	}
	printf("heredoc out: %d\n", fd[FD_OUT]);
	// Reset STDIN to its original state after here_doc processing
	if (dup2(shell->std_fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


