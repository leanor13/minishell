/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/03 14:14:42 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_command(t_arg *command, char **envp)
{
	pid_t	pid;

	if (!command)
		return (NEG_ERROR);
	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	else if (pid == 0)
	{
		dup_close(command->fd_in, STDIN_FILENO);
		dup_close(command->fd_out, STDOUT_FILENO);
		if (command->built_in_fn != NULL)
		{
			if (command->built_in_fn(envp, command->args_parsed, STDOUT_FILENO) == EXIT_FAILURE)
			{
				ft_putstr_nl("Built-in error", STDERR_FILENO);
				exit (NEG_ERROR);
			}
		}
		else if (execve(command->path, command->args_parsed, envp) == -1)
		{
			perror("Execve error");
			printf("path: %s", command->path);
			exit (NEG_ERROR);
		}
	}
	return (pid);
}

int	exec_pipe(t_arg *c_list, char **env)
{
	int	fd_pipe[2];
	int	status;
	t_arg *current;
	int	count;
	int i;

	if (!c_list)
		return (NEG_ERROR);
	current = c_list;
	count = args_count(c_list);
	while (current)
	{
		if (current->command)
		{
			if (pipe(fd_pipe) == -1)
			{
				perror("Error creating pipe");
				return (close_all_protected(), NEG_ERROR);
			}
			if (current->next == NULL && !current->out_file)
					current->fd_out = STDOUT_FILENO;
			else if (!current->out_file)
				current->fd_out = fd_pipe[FD_OUT];
			printf("fd_out: %d\n", current->fd_out);
			if (exec_command(current, env) < 0)
			{
				ft_close(fd_pipe[FD_OUT]);
				if (current->next == NULL)
					ft_close(fd_pipe[FD_IN]);
				return (close_all_protected(), NEG_ERROR);
			}
			if (!current->in_file)
				current->fd_in = fd_pipe[FD_IN];
			ft_close(fd_pipe[FD_OUT]);
			if (current->next == NULL)
				ft_close(fd_pipe[FD_IN]);
		}
		current = current->next;
	}
	ft_close(fd_pipe[FD_IN]);
	for (i = 0; i < count; i ++)
		waitpid(-1, &status, 0);
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

/* 
int	*handle_input(int ac, char **av)
{
	int	*fd_files;

	fd_files = malloc(sizeof(int) * 2);
	if (!fd_files)
	{
		perror("Failed to allocate memory for fd_files");
		exit (EXIT_FAILURE);
	}
	if (ft_strcmp(av[1], "here_doc") == 0)
		open_files_here_doc(ac, av, fd_files);
	else
	{
		fd_files[FD_IN] = open_file(ac, av, INPUT_FILE);
		fd_files[FD_OUT] = open_file(ac, av, OUTPUT_REWRITE);
	}
	if (fd_files[FD_OUT] < 0 || fd_files[FD_IN] < 0)
	{
		close_all_protected();
		free(fd_files);
		exit (EXIT_FAILURE);
	}
	return (fd_files);
} */

/* int	main_pipex(int ac, char **av, char **env)
{
	int			*fd_files;
	t_command	*command_list;
	int			status;

	validate_params(ac, av);
	fd_files = handle_input(ac, av);
	if ((ft_strcmp(av[1], "here_doc") == 0) && (ac--))
		av ++;
	command_list = build_command_list(ac, av, env);
	if (!command_list)
	{
		close_all_protected();
		return (free(fd_files), EXIT_FAILURE);
	}
	status = exec_pipe(command_list, fd_files, ac - 3, env);
	close_all_protected();
	free(fd_files);
	free_command_list(command_list, ac - 3);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
} */
