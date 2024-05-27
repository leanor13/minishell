/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:48:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/23 12:58:30 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

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

static int	open_fds(t_arg *command, t_shell *shell)
{
	int	i;
	// here_doc: add here here_doc case
	while (command)
	{
		if (command->here_doc != NULL)
		{
			here_doc(command, shell);
			command->in_file = "here_doc";
			command->fd_in = STDIN_FILENO;
		}
		else if (command->in_file_open && command->in_file_open[0]) 
		{
			i = 0;
			while (command->in_file_open[i])
			{
				command->fd_in = open_file(command->in_file_open[i], INPUT_FILE);
				if (command->fd_in == -1)
					perror("open input file");
				i++;
			}
		}
		if (command->out_file && command->out_file[0])
		{
			i = 0;
			while (command->out_file[i])
			{
				if (command->append)
					command->fd_out= open_file(command->out_file[i], OUTPUT_APPEND);
				else
					command->fd_out= open_file(command->out_file[i], OUTPUT_REWRITE);
				if (command->fd_out == -1)
					perror("open output file");
				i ++;
			}
		}
		if (ft_min(command->fd_in, command->fd_out) < 0)
		{
			command->command = NULL;
			return (EXIT_FAILURE);
		}
		command = command->next;
	}
	return (EXIT_SUCCESS);
}

int	executor_main(t_shell *shell)
{
	int		status;

	if (!shell->args_list)
		return (EXIT_SUCCESS);
	open_fds(shell->args_list, shell);
	if (build_command_list(shell) != EXIT_SUCCESS)
	{
		printf("build list failed\n");
		close_all_protected(shell);
		return (EXIT_FAILURE);
	}
	status = exec_pipe(shell);
	free_command_list(&shell->args_list);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
