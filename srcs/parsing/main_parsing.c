/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/02 17:34:50 by yioffe           ###   ########.fr       */
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
	lst1_1 = &(t_arg)
	{
		.append = false,
		.here_doc = false,
		.in_file = NULL,
		.out_file = NULL,
		.next = NULL,
		.args = "ls"
	};
	//(void)lst1_1;

	lst1 = &(t_arg)
	{
		.append = false,
		.here_doc = false,
		.in_file = NULL,
		.out_file = NULL,
		.next = lst1_1,
		.args = "cd srcs/"
	};

	//moved argc check to main flow
	while (1)	
	{
		//free_stackfinal(&shell->args_list); // I moved this to clean before next run. If run is final we will clean separately
		lst = NULL;
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		add_history(command); // do we need to remember if command was executed or not?	
		lst = ft_lexer(command, lst);
		lst = ft_parser(lst);
		(void)shell;
		// if (ft_strcmp(command, "test env") == 0)
		// 	print_env(shell->env_shell);
		// else if (ft_strcmp(command, "pipe 1") == 0)
		// 	lst = lst1;
		//free_stackfinal(&lst);
		//shell->args_list = lst;
		//if (shell->args_list != NULL)
		//	executor_main(shell);
		//ft_block_signals(); TODO: implement in the end
		//free(command); YOU DO NOT HAVE TO FREE IT READLINE FREEING EVERYTIME IT ONLY QUITS IF IT IS NULL
	}
	return (EXIT_SUCCESS);
}