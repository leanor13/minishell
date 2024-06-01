/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:39:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/01 11:12:37 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int type)
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

static void	handle_here_doc(t_arg *command, t_shell *shell)
{
	here_doc(command, shell);
	command->fd_in = STDIN_FILENO;
}

static void	open_input_files(t_arg *command)
{
	int	i;

	i = 0;
	while (command->in_file[i])
	{
		command->fd_in = open_file(command->in_file[i], INPUT_FILE);
		if (command->fd_in == -1)
			perror("open input file");
		i++;
	}
}

static void	open_output_files(t_arg *command)
{
	int	i;

	i = 0;
	while (command->out_file[i])
	{
		if (command->append)
			command->fd_out = open_file(command->out_file[i], OUTPUT_APPEND);
		else
			command->fd_out = open_file(command->out_file[i], OUTPUT_REWRITE);
		if (command->fd_out == -1)
			perror("open output file");
		i++;
	}
}

int	process_command_fds(t_arg *command, t_shell *shell)
{
	while (command)
	{
		if (command->here_doc != NULL)
			handle_here_doc(command, shell);
		else if (command->in_file && command->in_file[0])
			open_input_files(command);
		if (command->out_file && command->out_file[0])
			open_output_files(command);
		if (command->fd_in < 0 || command->fd_out < 0)
		{
			command->command = NULL;
			return (EXIT_FAILURE);
		}
		command = command->next;
	}
	return (EXIT_SUCCESS);
}
