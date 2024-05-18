/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:48:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/18 13:40:58 by yioffe           ###   ########.fr       */
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
	// here: go through all args and try to open input and output files. 
	//Check in what order. Check >> or > etc
	
	//if ((ft_strcmp(av[1], "here_doc") == 0) && (ac--))
	//	av ++;
	open_fds(shell->args_list, shell);
	if (build_command_list(shell) != EXIT_SUCCESS)
	{
		printf("build list failed\n");
		close_all_protected(shell);
		return (EXIT_FAILURE);
	}
	// in future - change env to shell->env_list
	// 
	status = exec_pipe(shell);
	//close_all_protected();
	//free(fd_files);
	free_command_list(&shell->args_list);
	//free(shell->args_list);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}