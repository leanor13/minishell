/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/14 16:19:27 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main_parsing(t_shell *shell)
{
	char *command = NULL;
	t_arg *lst;
	t_arg *lst1 = NULL;
	int saved_stdin = shell->std_fds[0]; // Save the original STDIN_FILENO

	lst = NULL;
	while (1)
	{
		printf("saved_stdin: %d, STDIN:%d, shell->std_fds[0]: %d\n", saved_stdin, STDIN_FILENO, shell->std_fds[0]);
		if (dup2(saved_stdin, STDIN_FILENO) == -1) // Reset STDIN_FILENO
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		lst = NULL;
		command = NULL;
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			exit(0);
		}
		add_history(command);
		lst = ft_lexer(command, lst);
		lst = ft_parser(lst);
		if (ft_strcmp(command, "test env") == 0)
			print_env(shell->env_list);
		else if (ft_strcmp(command, "pipe 1") == 0)
			lst = lst1;
		shell->args_list = lst;
		if (shell->args_list != NULL)
			executor_main(shell);
		free_stackfinal(&lst);
		free(command);

		// Reset STDIN_FILENO to the original terminal input after command processing
	}
	ft_close(saved_stdin); // Close the saved STDIN_FILENO descriptor
	return (EXIT_SUCCESS);
}
