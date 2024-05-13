/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/13 22:38:02 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main_parsing(t_shell *shell)
{
	(void)shell;
	char	*command = NULL;
	t_arg	*lst;
	// t_arg	*lst1 = NULL;
	// t_arg	*lst1_1 = NULL;

	// lst = NULL;
	// lst1_1 = &(t_arg)
	// {
	// 	.append = false,
	// 	.here_doc = false,
	// 	.in_file = NULL,
	// 	.out_file = NULL,
	// 	.next = NULL,
	// };
	// //(void)lst1_1;

	// lst1 = &(t_arg)
	// {
	// 	.append = false,
	// 	.here_doc = false,
	// 	.in_file = NULL,
	// 	.out_file = NULL,
	// 	.next = lst1_1,
	// };

	//moved argc check to main flow
	while (1)	
	{
		//free_stackfinal(&shell->args_list); // I moved this to clean before next run. If run is final we will clean separately
		lst = NULL;
		command = NULL;
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);// IT IS NOT EXITING FOR THE FIRST TIME??
			exit(0);
		}
		add_history(command); // it is not in the right space because we have to go back more times in exit
		lst = ft_lexer(command, lst);
		t_arg *current = lst;
   	 	while (current)
    	{	
		// printf("%sOUTPUT\n", current->out_file);
		// printf("%sHEREDOC\n", current->here_doc);
        	printf("string before parser: %s\n", current->str);
        	printf("type %i\n", current->type);
        	current = current->next;
   		}
		lst = ft_parser(lst);
		// if (ft_strcmp(command, "test env") == 0)
		// 	print_env(shell->env_list);
		// else if (ft_strcmp(command, "pipe 1") == 0)
		// 	lst = lst1;
		// shell->args_list = lst;
		// if (shell->args_list != NULL)
		// 	executor_main(shell);
		free_stackfinal(&lst);
		free(command);
		//ft_block_signals(); TODO: implement in the end
		//free(command); YOU DO NOT HAVE TO FREE IT READLINE FREEING EVERYTIME IT ONLY QUITS IF IT IS NULL
	}
	return (EXIT_SUCCESS);
}