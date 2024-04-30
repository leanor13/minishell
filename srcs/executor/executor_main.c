/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:48:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/30 13:00:48 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor_main(t_shell *shell)
{
	int		*fd_files;
	int		status;

	if (!shell->args_list)
		return (EXIT_SUCCESS);
	fd_files = malloc(2*sizeof(int));
	fd_files[0] = STDIN_FILENO;
	fd_files[1] = STDOUT_FILENO;
	//validate_params(ac, av);
	//fd_files = handle_input(ac, av);
	// here: go through all args and try to open input and output files. 
	//Check in what order. Check >> or > etc
	
	//if ((ft_strcmp(av[1], "here_doc") == 0) && (ac--))
	//	av ++;
	printf("env: %s\n", shell->env_original[0]);
	printf("env: %s\n", shell->env_original[1]);
	if (build_command_list(shell) != EXIT_SUCCESS)
	{
		close_all_protected();
		return (free(fd_files), EXIT_FAILURE);
	}
	// in future - change env to shell->env_shell
	status = exec_pipe(shell->args_list, fd_files, shell->env_original);
	close_all_protected();
	//free(fd_files);
	free_command_list(shell->args_list);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}