/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/21 20:58:39 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int	g_signal;

void	heredoc_handler_function(int sig)
{
	int	dev_null;

	if (sig == SIGINT)
	{
		dev_null = open("/dev/null", O_RDONLY);
		if (dev_null != -1)
		{
			dup2(dev_null, STDIN_FILENO);
			close(dev_null);
		}
		g_signal = 1;
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	heredoc_signal(void)
{
	struct sigaction	signal;
	struct sigaction	act;

	signal.sa_flags = 0;
	signal.sa_handler = &heredoc_handler_function;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigemptyset(&signal.sa_mask);
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
}

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

int	main_util(t_shell *shell)
{
	char	*command;
	t_arg	*lst;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	while (1)
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
		if (shell->should_exit)
		{
			exit_status = shell->exit_status;
			free_shell(shell);
			exit(exit_status);
		}
		main_signal();//we have to leave this from here*
		if (g_signal == 1) //WE HAVE TO LEAVE THIS HERE BECAUSE OF THE GLOBAL VARIABLE
			write(1, "\n", 1);
		start_minishell(lst, command, shell, exit_status);
	}
	return (EXIT_SUCCESS);// *until here
}
