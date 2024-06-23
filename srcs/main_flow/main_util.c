/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/23 11:26:45 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int	g_signal;

void	child_handler_function(int sig)
{
	if (sig == SIGINT)
		g_signal = 1;
	rl_on_new_line();
}

void	main_handler_function(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT)
		g_signal = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	dup_stds(t_shell *shell)
{
	if (dup2(shell->std_fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	if (dup2(shell->std_fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	if (dup2(shell->std_fds[2], STDERR_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main_util(t_shell *shell)
{
	char	*command;
	t_arg	*lst;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		if (dup_stds(shell) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (shell->should_exit)
		{
			exit_status = shell->exit_status;
			free_shell(shell);
			exit(exit_status);
		}
		main_signal();
		if (g_signal == 1)
			write(1, "\n", 1);
		start_minishell(lst, command, shell, exit_status);
	}
	return (EXIT_SUCCESS);
}
