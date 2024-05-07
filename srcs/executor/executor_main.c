/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:48:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/07 11:33:53 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	open_fds(t_arg *command)
{
	// here_doc: add here here_doc case
	while (command)
	{
		if (command->in_file)
			command->fd_in = open_file(command->in_file, INPUT_FILE);
		if (command->out_file)
		{
			if (command->append)
				command->fd_out= open_file(command->out_file, OUTPUT_APPEND);
			else
			{
				command->fd_out= open_file(command->out_file, OUTPUT_REWRITE);
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
	//validate_params(ac, av);
	//fd_files = handle_input(ac, av);
	// here: go through all args and try to open input and output files. 
	//Check in what order. Check >> or > etc
	
	//if ((ft_strcmp(av[1], "here_doc") == 0) && (ac--))
	//	av ++;
	open_fds(shell->args_list);
	if (build_command_list(shell) != EXIT_SUCCESS)
	{
		close_all_protected();
		return (EXIT_FAILURE);
	}
	// in future - change env to shell->env_list
	// 
	status = exec_pipe(shell->args_list, shell->env_2d);
	close_all_protected();
	//free(fd_files);
	free_command_list(&shell->args_list);
	//free(shell->args_list);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}