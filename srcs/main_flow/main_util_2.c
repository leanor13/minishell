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

void	start_minishell(t_arg *lst, char *command, \
t_shell *shell, int exit_status)
{
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
	{
		child_signal();
		executor_main(shell);
	}
	free_args(&shell->args_list);
	free(command);
	close_all_protected(shell);
}
