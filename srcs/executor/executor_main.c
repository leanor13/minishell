/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:48:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/01 17:32:00 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor_main(t_shell *shell)
{
	int	status;

	if (!shell->args_list)
		return (EXIT_SUCCESS);
	process_command_fds(shell->args_list, shell);
	if (build_command_list(shell) != EXIT_SUCCESS)
	{
		printf("build list failed\n");
		close_all_protected(shell);
		return (EXIT_FAILURE);
	}
	status = exec_pipe(shell);
	free_args(&shell->args_list);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
