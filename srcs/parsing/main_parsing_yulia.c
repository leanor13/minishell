/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_yulia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/24 15:49:09 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main_parsing(t_shell *shell)
{
	char *command = NULL;
	t_arg	*lst = NULL;

	//moved argc check to main flow
	while (1)	
	{
		free_stackfinal(&shell->args_list); // I moved this to clean before next run. If run is final we will clean separately
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		add_history(command); // do we need to remember if command was executed or not?
		// I think we need to allocate memory for lst somewhere. Maybe I just did not find it yet.
		//lst = ft_lexer(command);
		//lst = ft_parser(lst);
		shell->args_list = lst;
		if (shell->args_list != NULL)
			executor_main(shell);
		//ft_block_signals(); TODO: implement in the end
		//free(command); YOU DO NOT HAVE TO FREE IT READLINE FREEING EVERYTIME IT ONLY QUITS IF IT IS NULL
	}
	return (EXIT_SUCCESS);
}
