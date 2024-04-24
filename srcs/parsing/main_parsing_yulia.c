/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_yulia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/24 14:44:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main_parsing(t_shell *shell)
{
	char *command = NULL;
	t_arg	*lst;

	//moved argc check to main flow
	while (1)	
	{
		free_stackfinal(shell->args_list); // I moved this to clean before next run. If run is final we will clean separately
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		add_history(command);
		// I think we need to allocate memory for lst somewhere. maybe I just did not find it yet.
		lst = ft_lexer(command);
		lst = ft_parser(&lst);
		shell->args_list = lst;
		if (shell->args_list != NULL)
			executor_main(shell);
		//signal at the end for ctrl \ + ctrl C
		//free(command); YOU DO NOT HAVE TO FREE IT READLINE FREEING EVERYTIME IT ONLY QUITS IF IT IS NULL
	}
	return (EXIT_SUCCESS);
}
