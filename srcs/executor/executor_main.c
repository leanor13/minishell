/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:48:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/29 18:36:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor_main(t_shell *shell)
{
	int			*fd_files;
	t_command	*command_list;
	int			status;

	if (!shell->args_list)
		return (EXIT_SUCCESS);
	//validate_params(ac, av);
	//fd_files = handle_input(ac, av);
	// here: go through all args and try to open input and output files. 
	//Check in what order. Check >> or > etc
	
	//if ((ft_strcmp(av[1], "here_doc") == 0) && (ac--))
	//	av ++;
	command_list = build_command_list(shell->args_list, &(shell->env_original));
	// in future - change env to shell->env_shell
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
}