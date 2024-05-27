/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/27 17:04:32 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void read_input(int fd[2], char **limiters, t_shell shell)
{
	char *line;
	int lim_count = 0;  // Total number of limiters
	int i = 0;          // Current limiter index

	ft_close(fd[0]);    // Close the read end of the pipe in child process
	while (limiters[lim_count]) {
		lim_count++;    // Count the total number of limiters
	}
	while (true) 
	{
		write(shell.std_fds[FD_OUT], "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL) {
			// Handle error if line is null
			close_all_unprotected();
			perror("Error reading from standard input");
			exit(EXIT_FAILURE);
		}
		// Check if current line matches the current limiter
		if (strncmp(line, limiters[i], strlen(limiters[i])) == 0 && strlen(line) == strlen(limiters[i]) + 1) {
			free(line); // Free the line as it's a delimiter
			i++;        // Move to the next limiter
			if (i == lim_count) {
				// If it was the last delimiter, break out of the loop
				break;
			}
			continue;   // Continue to next iteration to skip writing the delimiter
		}
		if (i == lim_count - 1) {
			// Only write to pipe if all limiters except the last have been passed
			write(fd[1], line, ft_strlen(line));
		}
		free(line);
	}
	ft_close(fd[1]);    // Close the write end of the pipe after finishing reading
}



static void	ft_error_forking(void)
{
	perror("Error forking");
	exit (EXIT_FAILURE);
}

int	here_doc(t_arg *command, t_shell *shell)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	char	**limiters = command->here_doc;
	//int		i = 0;

	shell->here_doc = true;
	exit_pipe_error(fd);
	pid = fork();
	if (pid < 0)
		ft_error_forking();
	else if (pid == 0)
	{
		read_input(fd, limiters, *shell);
		close_all_unprotected();
		exit(EXIT_SUCCESS);
	}
		close(fd[1]);  
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]); // Close the read end now that it's duplicated
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			// Handle potential cleanup and error reporting
			close_all_protected(shell);
			return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


/* void	open_files_here_doc(int ac, char **av, int *fd_files)
{
	fd_files[FD_OUT] = open_file(ac, av, HERE_DOC);
	if (fd_files[FD_OUT] == -1)
	{
		free(fd_files);
		close_all_protected();
		exit(EXIT_FAILURE);
	}
	here_doc(av[2], fd_files);
	fd_files[FD_IN] = STDIN_FILENO;
} */


