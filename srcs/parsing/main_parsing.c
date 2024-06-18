/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/10 18:57:51 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile int	g_sig;

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 1;
		write(1, "\n", 1);
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

void	set_heredoc_handler(void)
{
	struct sigaction	sa;
	struct sigaction	act;

	sa.sa_flags = 0;
	sa.sa_handler = &heredoc_handler;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
}

void	child_handler(int sig)
{
	rl_on_new_line();
}

void	prompt_handler(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT)
		g_sig = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_child_handler(void)
{
	struct sigaction	sa;
	struct sigaction	act;

	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &act, NULL);
}

void	set_prompt_handler(void)
{
	struct sigaction	sa;
	struct sigaction	act;

	sa.sa_handler = &prompt_handler;
	sa.sa_flags = SA_RESTART;
	act.sa_flags = SA_RESTART;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
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
		set_prompt_handler();
		if (g_sig == 0)
			command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		else
			command = readline("\n\033[1;36mminishell\033[1;32m$\033[0;0m");
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
			set_child_handler();
			executor_main(shell);
		}
		free_args(&shell->args_list);
		free(command);
		close_all_protected(shell);
	}
	return (EXIT_SUCCESS);
}
