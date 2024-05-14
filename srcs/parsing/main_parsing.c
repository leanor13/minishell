/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/14 15:47:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main_parsing(t_shell *shell)
{
	char	*command = NULL;
	t_arg	*lst;
	t_arg	*lst1 = NULL;
	t_arg	*lst1_1 = NULL;

	lst = NULL;
	while (1)	
	{
		lst = NULL;
		command = NULL;
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			exit(0);
		}
		add_history(command); // it is not in the right space because we have to go back more times in exit
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
		//ft_block_signals(); TODO: implement in the end
		//free(command); YOU DO NOT HAVE TO FREE IT READLINE FREEING EVERYTIME IT ONLY QUITS IF IT IS NULL
	}
	return (EXIT_SUCCESS);
}