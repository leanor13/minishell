/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/23 10:16:25 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	char *command = NULL;
	t_arg	*lst;
//	t_arg_pass	*cleared_command;
	if (argc != 1)
	{
		ft_printf("RUN THE CODE WITHOUT ARGUMENTS\n");// YULIA STDERROR
		exit(0);
	}
	while (1)	
	{
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_printf("exit\n");
				exit(0);//YULIA maybe error, perror, it is just simply quit the program, because it is exit command
		}
		add_history(command);
		lst = ft_lexer(command);
		lst = ft_parser(&lst);
		free_stackfinal(&lst);// YULIA FOR YOU TO DEL THE WHOLE LIST
		//signal at the end for ctrl \ + ctrl C
	//UPDATE ENV!!
	//Replace the environment variables into a linked list so you can delete or add
	//later using export and unset builtins. 
	//In addition to displaying them using env or export (without arguments) builtins 
		//free(command); YOU DO NOT HAVE TO FREE IT READLINE FREEING EVERYTIME IT ONLY QUITS IF IT IS NULL
	}
}
