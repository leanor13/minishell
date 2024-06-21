/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/21 18:53:29 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile int	g_signal;

void	heredoc_handler_function(int sig)
{
	int	dev_null;

	if (sig == SIGINT)
	{
		dev_null = open("/dev/null", O_RDONLY);
		if (dev_null != -1)
		{
			//printf("here\n");
			dup2(dev_null, STDIN_FILENO);
			close(dev_null);
		}
		g_signal = 1;
		//write(1, "\n", 1);
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
	{
		g_signal = 1;  // Ensuring the new line is printed to STDOUT
	}
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

void	child_signal(void)
{
	struct sigaction	signal;
	struct sigaction	act;

	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	signal.sa_handler = &child_handler_function;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &signal, NULL);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGTERM, &act, NULL);
}

void	main_signal(void)
{
	struct sigaction	signal;
	struct sigaction	act;

	signal.sa_handler = &main_handler_function;
	signal.sa_flags = SA_RESTART;
	act.sa_flags = SA_RESTART;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
}

int	main_parsing(t_shell *shell)
{
	char	*command;
	t_arg	*lst;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	command = NULL;
	lst = NULL;
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
		lst = NULL;
		command = NULL;
		main_signal();
		if (g_signal == 1)
			write(1, "\n", 1);
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			free_shell(shell);
			exit(exit_status);
		}
		add_history(command);
		lst = ft_lexer(command, lst);
		if (lst)
			lst = ft_parser(lst, shell);
		if (lst)
			shell->args_list = lst;
		if (shell->args_list != NULL)
		{
			child_signal();
			executor_main(shell);
		}
		free_args(&shell->args_list);
		free(command);
		close_all_protected(shell);
	}
	return (EXIT_SUCCESS);
}
