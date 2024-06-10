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

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("Signal SIGINT received, terminating process...\n");
        exit(EXIT_FAILURE);
    }
}

int	main_parsing(t_shell *shell)
{
	char	*command;
	t_arg	*lst;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	command = NULL;
	lst = NULL;
	signal(SIGINT, signal_handler);
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
			executor_main(shell);
		free_args(&shell->args_list);
		free(command);
		close_all_protected(shell);
	}
	return (EXIT_SUCCESS);
}
